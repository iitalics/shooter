#pragma once



class Player
{
public:
	explicit Player (const vec2f& pos);
	~Player ();

	inline float rotation () const { return _rotation; }
	inline vec2f position () const { return _position; }

	inline float radius () const { return 21; }

	void update (float dt);
	void draw ();

private:
	float _rotation;
	vec2f _position;
	vec2f _velocity;
};
