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

	static constexpr void* UserData_Player = (void*)0x1;
	static constexpr void* UserData_Wall   = (void*)0x2;

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

class FunctionCallback
	: public b2RayCastCallback
{
public:
	template <typename F>
	inline FunctionCallback (F func)
		: _func(func) {}
	
	virtual float32 ReportFixture (b2Fixture* fix,
								const b2Vec2& pos, 
								const b2Vec2& normal,
								float32 fraction);
private:
	std::function<float(b2Fixture*,
			            const b2Vec2&,
			            const b2Vec2&,
						float)>
			_func;
};
