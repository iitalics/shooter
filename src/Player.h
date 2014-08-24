#pragma once

class Game;

class Player
{
public:
	// fuck
	typedef int Move;
	enum
	{
		None = 0,
		Right = 1,
		Left = 2,
		Up = 4,
		Down = 8,

		MoveX = Left | Right,
		MoveY = Up | Down,
	};


	explicit Player (const vec2f& pos);
	~Player ();

	// fields
	inline float rotation () const { return _rotation; }
	inline vec2f position () const { return _position; }
	inline Move move () const { return _move; }

	// properties
	inline float radius () const { return 24; }
	float speed () const;

	// actions
	void update (Game* game, float dt);
	void draw ();

	void move (Move m);
	void stop (Move m);

private:
	float _rotation;
	vec2f _position;
	vec2f _velocity;
	Move _move;
};
