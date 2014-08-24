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
	inline int radius () const { return 24; }
	int speed () const;

	// actions
	void update (Game* game, double dt);
	void draw ();

	void move (Move m);
	void stop (Move m);
	void turn (float rot, bool instant = false);

private:
	float _rotation,
		_destRotation;
	
	vec2f _position;
	vec2f _velocity;
	Move _move;
};
