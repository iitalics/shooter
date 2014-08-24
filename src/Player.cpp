#include "include.h"
#include "Player.h"
#include "Game.h"


Player::Player (const vec2f& pos)
	: _rotation(0),
	  _destRotation(0),
	  _position(pos),
	  _velocity(),
	  _move(None)
{ }

Player::~Player () {}




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
	return 450;
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
		else
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
		else
			_velocity.y = math::min(0.0,
						_velocity.y + speedup * dt);

	_position += _velocity * dt;

	// TODO: not this
	_rotation = _destRotation;
}


void Player::draw ()
{
	glPushMatrix();
	_position.glTranslate();
	glRotatef(math::degrees(_rotation), 0, 0, 1);
	
	auto r = radius();

	// draw a circle
	const auto vertices = 60;

	color(0, .5f, 1).gl();
	glBegin(GL_LINE_STRIP);
	for (auto i = 0; i <= vertices; i++)
		(vec2f::unit(i * (math::pi * 2 / vertices)) * r).gl();
	vec2f().gl();
	glEnd();

	glPopMatrix();
}
