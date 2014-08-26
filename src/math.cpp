#include "include.h"
#include "Game.h"
#include <random>
#include <chrono>

namespace math
{
    vec2f parseVec2(const std::string& str)
    {
        std::stringstream ss(str);
        float x, y;

        while (!ss.eof() && isspace(ss.peek()))
            ss.get();
        ss >> x;
        if (!ss.eof() && ss.peek() == ',')
            ss.get();
        while (!ss.eof() && isspace(ss.peek()))
            ss.get();
        ss >> y;

        return vec2<float>(x, y);
    }
    rect parseRect(const std::string& str)
    {
        std::istringstream ss(str);
        decltype(rect().x) data[4];

        while (!ss.eof() && isspace(ss.peek()))
            ss.get();
        ss >> data[0];

        for (size_t i = 1; i < (sizeof(data) / sizeof(*data)); i++)
        {
            if (!ss.eof() && ss.peek() == ',')
                ss.get();
            while (!ss.eof() && isspace(ss.peek()))
                ss.get();
            ss >> data[i];
        }

        return rect(data[0], data[1], data[2], data[3]);
    }
	
	fp_t random()
	{
		// oh boy oh boy
		static std::default_random_engine gen(std::chrono::system_clock::now().
									time_since_epoch().
									count());
		
		return gen() / fp_t(gen.max());
	}
};

u32 color::rgb() const
{
    auto red   = u8(math::clamp<float>(r, 0, 1) * 255);
    auto green = u8(math::clamp<float>(g, 0, 1) * 255);
    auto blue  = u8(math::clamp<float>(b, 0, 1) * 255);

    // 0xrrggbb
    return (red << 16)  |
           (green << 8) |
           blue;
}
u32 color::rgba() const
{
    auto red   = u8(math::clamp<float>(r, 0, 1) * 255);
    auto green = u8(math::clamp<float>(g, 0, 1) * 255);
    auto blue  = u8(math::clamp<float>(b, 0, 1) * 255);
    auto alpha = u8(math::clamp<float>(a, 0, 1) * 255);

    // 0xaarrggbb
    return (alpha << 24) |
           (red << 16)   |
           (green << 8)  |
           blue;
}

bool color::operator== (const color& other) const
{
	return r == other.r &&
			g == other.g &&
			b == other.g &&
			a == other.a;
}

void color::glApplyClear() const
{
    glClearColor(r, g, b, 1);
    glClear(GL_COLOR_BUFFER_BIT);
}

color color::lerp(float amt, const color& a, const color& b)
{
    return color(math::lerp(amt, a.r, b.r),
                 math::lerp(amt, a.g, b.g),
                 math::lerp(amt, a.b, b.b),
                 math::lerp(amt, a.a, b.a));
}
color color::lerpRGB(float amt, const color& a, const color& b, float alpha)
{
    return color(math::lerp(amt, a.r, b.r),
                 math::lerp(amt, a.g, b.g),
                 math::lerp(amt, a.b, b.b),
                 alpha);
}


vec2f from_b2 (const b2Vec2& inp)
{
	return vec2f {
		inp.x * Game::WorldScale,
		inp.y * Game::WorldScale
	};
}
b2Vec2 to_b2 (const vec2f& inp)
{
	return b2Vec2 {
		float(inp.x / Game::WorldScale),
		float(inp.y / Game::WorldScale)
	};
}

