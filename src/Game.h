#pragma once
#include <memory>
#include <Box2D/Box2D.h>
#include "Input.h"

class Player;
class Display;
class Map;

class Game
{
public:
	explicit Game ();
	~Game ();

	enum
	{
		WorldScale = 64
	};

	// fields
	inline std::vector<Player>& players () { return _players; }
	inline b2World* world () const { return _world.get(); }
	inline Map* map () const { return _map.get(); }

	// properties
	Player* userPlayer ();

	// actions
	void update (double dt);
	void updateInput (Display* disp, const vec2f& cam, double dt);

	void drawOverlay (Display* disp);
private:
	std::vector<Player> _players;
	Input _input;

	std::unique_ptr<b2World> _world;
	std::unique_ptr<Map> _map;
};
