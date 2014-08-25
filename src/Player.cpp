#include "include.h"
#include "Player.h"
#include "Game.h"


Player::Player (Game* game, const vec2f& pos)
	: _game(game),
	  _rotation(0),
	  _destRotation(0),
	  _velocity(),
	  _move(None),
	  _body(nullptr)
{
	generateBody(pos);
}

Player::~Player () {}




b2Body* Player::generateBody (const vec2f& pos)
{
	auto world = _game->world();
	
	if (_body != nullptr)
		world->DestroyBody(_body);
	
	b2BodyDef def;
	def.type = b2_dynamicBody;
	def.position = { float(pos.x / Game::WorldScale),
		             float(pos.y / Game::WorldScale) };

	b2CircleShape shape;
	shape.m_radius = Radius / float(Game::WorldScale);

	_body = world->CreateBody(&def);
	_body->CreateFixture(&shape, 1.f);

	return _body;
}


vec2f Player::position () const
{
	if (_body)
	{
		auto pos = _body->GetPosition();
		return vec2f(pos.x * Game::WorldScale,
					 pos.y * Game::WorldScale);
	}
	else
		return vec2f();
}



// input actions
void Player::move (Move m)
{
	if (m & MoveX)
		_move = (_move & ~MoveX) | (m & MoveX);
	else if (m & MoveY)
		_move = (_move & ~MoveY) | (m & MoveY);
}
void Player::stop (Move m)
{
	_move &= ~m;
}
void Player::turn (float rot, bool instant)
{
	_destRotation = rot;

	if (instant)
		_rotation = rot;
}



int Player::speed () const
{
	return 340;
}


void Player::update (Game* game, double dt)
{
	const auto speedup = speed() * 6;
	
	// FUCK
	if (_move & Right)
		_velocity.x = math::min(double(speed()),
						_velocity.x + speedup * dt);
	else if (_move & Left)
		_velocity.x = math::max(-double(speed()),
						_velocity.x - speedup * dt);
	else
		if (_velocity.x > 0)
			_velocity.x = math::max(0.0,
						_velocity.x - speedup * dt);
		else if (_velocity.x < 0)
			_velocity.x = math::min(0.0,
						_velocity.x + speedup * dt);
	
	if (_move & Down)
		_velocity.y = math::min(double(speed()),
						_velocity.y + speedup * dt);
	else if (_move & Up)
		_velocity.y = math::max(-double(speed()),
						_velocity.y - speedup * dt);
	else
		if (_velocity.y > 0)
			_velocity.y = math::max(0.0,
						_velocity.y - speedup * dt);
		else if (_velocity.y < 0)
			_velocity.y = math::min(0.0,
						_velocity.y + speedup * dt);

	b2Vec2 vel;
	vel.x = float(_velocity.x / Game::WorldScale);
	vel.y = float(_velocity.y / Game::WorldScale);
	_body->SetLinearVelocity(vel);
}


void Player::draw ()
{
	glPushMatrix();
	position().glTranslate();
	glRotatef(math::degrees(_rotation), 0, 0, 1);
	
	const auto r = Radius;

	// draw a circle
	const auto vertices = 60;

	color(0, .5f, 1).gl();
	glBegin(GL_LINE_STRIP);
	for (auto i = 0; i <= vertices; i++)
		(vec2f::unit(i * (math::pi * 2 / vertices)) * r).gl();

	vec2f().gl(); // line from edge to center

	glEnd();

	glPopMatrix();
}
