#include "include.h"
#include "Map.h"
#include "Game.h"

Map::Map (Game* game)
{
	const auto nodes = 20;
	_ground.reserve(nodes);

	for (auto i = 0; i < nodes; i++)
		_ground.push_back(vec2f(
					math::random(width()),
					math::random(height())));

	_obstacles.push_back(
			obstacle({
				{ 30, 30 },
				{ 320, 35 },
				{ 310, 300 },
				{ 30, 310 } }));

	for (auto& b : _obstacles)
		b.createBody(game);
}

Map::~Map () {}


Map::obstacle::obstacle (const std::vector<vec2f>& v)
	: numVertices(math::min<int>(v.size(), MaxVertices))
{
	for (int i = 0; i < numVertices; i++)
		vertices[i] = v[i];
}

b2Body* Map::obstacle::createBody (Game* game)
{
	auto world = game->world();

	b2BodyDef def;
	def.position = { 0, 0 };
	def.type = b2_staticBody;

	b2PolygonShape shape;
	b2Vec2 points[MaxVertices];

	for (int i = 0; i < numVertices; i++)
		points[i] = to_b2(vertices[i]);
	shape.Set(points, numVertices);

	body = world->CreateBody(&def);
	auto fix = body->CreateFixture(&shape, 0);
	fix->SetUserData(Game::UserData_Wall);

	return body;
}

void Map::draw (Display* disp, const vec2f& camera)
{
	color(.1f).gl();
	glBegin(GL_LINE_STRIP);
	for (auto& pos : _ground)
		pos.gl();
	glEnd();

	color(1, 0, 0).gl();
	glBegin(GL_LINE_STRIP);
	for (auto& o : _obstacles)
	{
		o.vertices[0].gl();
		for (auto i = o.numVertices; i-- > 0; )
			o.vertices[i].gl();
	}
	glEnd();
}
