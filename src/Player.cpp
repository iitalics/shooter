#include "include.h"
#include "Player.h"


Player::Player (const vec2f& pos)
	: _rotation(0),
	  _position(pos),
	  _velocity()
{ }

Player::~Player () {}




void Player::update (float dt)
{
	_position += _velocity * dt;
}


void Player::draw ()
{
	glPushMatrix();
	_position.glTranslate();
	
	auto r = radius();

	color(1, 0, 0).gl(); // red
	glBegin(GL_QUADS);
	rect(-r, -r, r * 2, r * 2).gl();
	glEnd();

	glPopMatrix();
}
