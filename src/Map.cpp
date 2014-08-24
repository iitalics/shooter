#include "include.h"
#include "Map.h"

Map::Map ()
{
	const auto nodes = 40;
	_ground.reserve(nodes);

	for (auto i = 0; i < nodes; i++)
		_ground.push_back(vec2f(
					math::random(width()),
					math::random(height())));
}

Map::~Map () {}


void Map::draw (Display* disp, const vec2f& camera)
{
	color(.1f).gl();
	glBegin(GL_LINE_STRIP);
	for (auto& pos : _ground)
		pos.gl();
	glEnd();
}
