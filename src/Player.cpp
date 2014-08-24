#include "include.h"
#include "Player.h"
#include "Game.h"


Player::Player (const vec2f& pos)
	: _rotation(0),
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
void Player::stop (Move m) { _move &= ~m; }



float Player::speed () const
{
	return 450;
}


void Player::update (Game* game, float dt)
{
	const int speedup = speed() * 6;
	
	// FUCK
	if (_move & Right)
		_velocity.x = math::min(speed(),
						_velocity.x + speedup * dt);
	else if (_move & Left)
		_velocity.x = math::max(-speed(),
						_velocity.x - speedup * dt);
	else
		if (_velocity.x > 0)
			_velocity.x = math::max(0,
						_velocity.x - speedup * dt);
		else
			_velocity.x = math::min(0,
						_velocity.x + speedup * dt);
	
	if (_move & Down)
		_velocity.y = math::min(speed(),
						_velocity.y + speedup * dt);
	else if (_move & Up)
		_velocity.y = math::max(-speed(),
						_velocity.y - speedup * dt);
	else
		if (_velocity.y > 0)
			_velocity.y = math::max(0,
						_velocity.y - speedup * dt);
		else
			_velocity.y = math::min(0,
						_velocity.y + speedup * dt);

	_position += _velocity * dt;
}


void Player::draw ()
{
	glPushMatrix();
	_position.glTranslate();
	glRotatef(math::degrees(_rotation), 0, 0, 1);
	
	color(0, .2f, 1).gl(); // red

	auto r = radius();
	rect(-r, -r, r * 2, r * 2).glQuad();

	glPopMatrix();
}
