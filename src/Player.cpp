#include "include.h"
#include "Player.h"
#include "Game.h"


Player::Player (const vec2f& pos)
	: _rotation(0),
	  _position(pos),
	  _velocity()
{ }

Player::~Player () {}




void Player::update (Game* game, float dt)
{
	_position += _velocity * dt;
}


void Player::draw ()
{
	glPushMatrix();
	_position.glTranslate();
	
	color(1, 0, 0).gl(); // red

	auto r = radius();
	rect(-r, -r, r * 2, r * 2).glQuad();

	glPopMatrix();
}
