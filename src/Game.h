#pragma once
#include <memory>
#include "Input.h"

class Player;
class Display;
class Map;

class Game
{
public:
	explicit Game ();
	~Game ();

	// fields
	inline std::vector<Player>& players () { return _players; }
	inline Map* map () const { return _map.get(); }

	// properties
	Player* userPlayer ();

	// actions
	void update (double dt);
	void updateInput (Display* disp, const vec2f& cam, double dt);
private:
	std::vector<Player> _players;
	Input _input;

	std::unique_ptr<Map> _map;
};
