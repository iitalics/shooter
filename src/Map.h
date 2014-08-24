#pragma once

#include "Display.h"

// this is just temporary
class Map
{
public:
	Map ();
	~Map ();

	// fields
	inline int width () const { return 3000; }
	inline int height () const { return 2000; }
	
	// properties
	inline vec2f size () const { return vec2f(width(), height()); }

	// actions
	void draw (Display* disp, const vec2f& camera);

private:
	std::vector<vec2f> _ground;
};
