#pragma once

class Game;

class Player
{
public:
	explicit Player (const vec2f& pos);
	~Player ();

	// fields
	inline float rotation () const { return _rotation; }
	inline vec2f position () const { return _position; }

	// properties
	inline float radius () const { return 21; }


	// actions
	void update (Game* game, float dt);
	void draw ();

	inline void move (const vec2f& dest) { _position = dest; }

private:
	float _rotation;
	vec2f _position;
	vec2f _velocity;
};
