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
private:
	std::vector<Player> _players;
	Input _input;
};
