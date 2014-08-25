#pragma once
#include <Box2D/Box2D.h>

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

		Radius = 24
	};


	explicit Player (Game* game, const vec2f& pos);
	~Player ();

	// fields
	inline float rotation () const { return _rotation; }
	inline Move move () const { return _move; }

	// properties
	vec2f position () const;
	int speed () const;

	// actions
	void update (Game* game, double dt);
	void draw ();
	
	b2Body* generateBody (const vec2f& pos);

	// input actions
	void move (Move m);
	void stop (Move m);
	void turn (float rot, bool instant = false);

private:
	Game* _game;
	float _rotation,
		_destRotation;
	
	vec2f _velocity;
	Move _move;
	
	b2Body* _body;
};
