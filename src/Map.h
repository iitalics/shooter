#pragma once
#include <Box2D/Box2D.h>
#include "Display.h"

class Game;

class Map
{
public:
	explicit Map (Game* game);
	~Map ();

	// pod structs
	struct obstacle
	{
		enum { MaxVertices = 8 };

		explicit obstacle (const std::vector<vec2f>& v);

		b2Body* createBody (Game* game);

		int numVertices;
		vec2f vertices[MaxVertices];
		b2Body* body;
	};
	using obstacles_t = std::vector<obstacle>;

	// fields
	inline int width () const { return 2000; }
	inline int height () const { return 1000; }
	inline const obstacles_t& obstacles () const { return _obstacles; }
	
	// properties
	inline vec2f size () const { return vec2f(width(), height()); }

	// actions
	void draw (Display* disp, const vec2f& camera);

private:
	std::vector<vec2f> _ground;
	obstacles_t _obstacles;
};
