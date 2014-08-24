#pragma once
#include "Input.h"

class Player;
class Display;

class Game
{
public:
	explicit Game ();
	~Game ();

	// fields
	inline std::vector<Player>& players () { return _players; }

	// properties
	Player* userPlayer ();

	// actions
	void update (float dt);
	void updateInput (Display* disp, float dt);

	void drawMap (Display* disp, const vec2f& camera); // GameView.cpp
private:
	std::vector<Player> _players;
	Input _input;

	std::vector<vec2f> _map;
};
