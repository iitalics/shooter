#pragma once

#include <cmath>
#include <string>
#include <sstream>


typedef uint_fast64_t u64;
typedef uint_fast32_t u32;
typedef uint_fast16_t u16;
typedef uint_fast8_t  u8;
typedef unsigned int uint;


template <typename T>
struct vec2
{
    T x, y;

    inline constexpr vec2 ()
        : x(0), y(0) {}
    inline constexpr vec2 (T _x)
        : x(_x), y(_x) {}
    inline constexpr vec2 (T _x, T _y)
        : x(_x), y(_y) {}
    template <typename Q>
    inline constexpr vec2 (const vec2<Q>& a)
        : x(T(a.x)), y(T(a.y)) {}

    vec2<T> operator+ (const vec2<T>& a) const
        { return vec2<T>(x + a.x, y + a.y); }
    vec2<T> operator- (const vec2<T>& a) const
        { return vec2<T>(x - a.x, y - a.y); }
    vec2<T> operator* (T a) const
        { return vec2<T>(x * a, y * a); }
    vec2<T> operator/ (T a) const
        { return vec2<T>(x / a, y / a); }
    vec2<T> operator- () const
        { return vec2<T>(-x, -y); }

	template <typename Q>
    bool operator== (const vec2<Q>& a) const
        { return a.x == x && a.y == y; }

    vec2<T> operator= (const vec2<T>& a) { x = a.x; y = a.y; return *this; }
    vec2<T> operator+= (const vec2<T>& a)
        { x += a.x; y += a.y; return *this; }
    vec2<T> operator-= (const vec2<T>& a)
        { x -= a.x; y -= a.y; return *this; }
    vec2<T> operator*= (T a)
        { x *= a; y *= a; return *this; }
    vec2<T> operator/= (T a)
        { x /= a; y /= a; return *this; }


    T mag () const { return sqrtf(x * x + y * y); }
    static vec2<T> unit (float rot) { return vec2<T>(cosf(rot), sinf(rot)); }

    T distance (const vec2<T>& b) const { return (*this - b).mag(); }
    std::string str () const
    {
        std::stringstream ss;
        ss << x << ", " << y;
        return ss.str();
    }
    inline void gl () const { glVertex2f((float)x, (float)y); }
    inline void glTranslate () const { glTranslatef((float)x, (float)y, 0); }
};


template <typename T>
struct rectangle
{
    T x, y, width, height;

    inline constexpr rectangle ()
        : x(0), y(0), width(0), height(0) {}
    inline constexpr rectangle (T _x, T _y, T _w, T _h)
        : x(_x), y(_y), width(_w), height(_h) {}
    inline constexpr rectangle (const rectangle<T>& a)
        : x(a.x), y(a.y), width(a.width), height(a.height) {}

    inline rectangle (const vec2<T>& _pos, const vec2<T>& _size)
        : x(_pos.x), y(_pos.y), width(_size.x), height(_size.y) {}

    void gl ()
    {
        glVertex2f((float)x, (float)y);
        glVertex2f((float)(x + width), (float)y);
        glVertex2f((float)(x + width), (float)(y + height));
        glVertex2f((float)x, (float)(y + height));
    }

    rectangle<T> operator+ (const vec2<T>& a) const
        { return rectangle<T>(x + a.x, y + a.y, width, height); }
    rectangle<T> operator- (const vec2<T>& a) const
        { return rectangle<T>(x - a.x, y - a.y, width, height); }
    rectangle<T> operator* (T a) const
        { return rectangle<T>(x, y, width * a, height * a); }
    rectangle<T> operator/ (T a) const
        { return rectangle<T>(x, y, width / a, height / a); }
    bool operator= (const rectangle<T>& a) const
        { return a.x == x && a.y == y && a.width == width && a.height == height; }

    inline vec2<T> pos () const
        { return vec2<T>(x, y); }
    inline vec2<T> size () const
        { return vec2<T>(width, height); }

    inline T right () const { return x + width; }
    inline T bottom () const { return y + height; }

    bool intersects (const rectangle<T>& a)
    {
        return x < a.right() && a.x < right() &&
            y < a.bottom() && a.y << bottom();
    }
};


struct color
{
    float r, g, b, a;

    inline constexpr color (float _r, float _g, float _b, float _a)
        : r(_r), g(_g), b(_b), a(_a) {}
    inline constexpr color (float _r, float _g, float _b)
        : r(_r), g(_g), b(_b), a(1) {}
    inline constexpr color (float _grey, float _a = 1)
        : r(_grey), g(_grey), b(_grey), a(_a) {}

    Uint32 rgb () const;
    Uint32 rgba () const;
	
    bool operator== (const color& x) const;
	inline bool operator!= (const color& x) const { return !(*this == x); }

    color operator* (float alpha) const
        { return color(r, g, b, a * alpha); }
    color operator+ (const color& other) const
        { return lerpRGB(other.a, *this, other) * a; }
	
    void gl () const { glColor4f(r, g, b, a); }
    void glApplyClear () const;

    static color lerp (float amt, const color& a, const color& b);
    static color lerpRGB (float amt, const color& a, const color& b, float alpha = 1);
};


namespace math
{
    inline float constexpr min (float a, float b)
        { return (a < b) ? a : b; }
    inline float constexpr max (float a, float b)
        { return (a > b) ? a : b; }
    float constexpr clamp (float v, float mn, float mx)
        { return (v < mn) ? mn : ((v > mx) ? mx : v); }

    template <typename T>
    T constexpr lerp (float amount, T x, T y)
        { return T(x + (y - x) * amount); }

    static const float constexpr pi = 3.1415926535f;
    static inline float constexpr degrees (float q) { return q * (180.f / pi); }
    static inline float constexpr radians (float q) { return q * (pi / 180.f); }

    float random();
	inline float random (float n) { return random() * n; }
	inline float random (float a, float b) { return a + random(b - a); }
	
    vec2<float> parseVec2 (const std::string& str);
    rectangle<float> parseRect (const std::string& str);
};

template <typename T>
inline std::ostream& operator<< (std::ostream& stream, const vec2<T>& o)
{
	return stream << "(" << o.x << ", " << o.y << ")";
}

template <typename T>
inline std::ostream& operator<< (std::ostream& stream, const rectangle<T>& o)
{
	return stream << "[" << o.x << ", " << o.y << ", "
		          << o.width << ", " << o.height << "]";
}

typedef vec2<float> vec2f;
typedef vec2<int> vec2i;
typedef rectangle<float> rect;
