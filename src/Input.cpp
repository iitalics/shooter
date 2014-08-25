#include "include.h"
#include "Game.h"
#include "Display.h"


Input::Input (Game* game)
	: _game(game)
{ }


void Input::update (Display* disp, const vec2f& camera, double dt)
{
	auto player = _game->userPlayer();
	if (!player)
		return;

	auto r = SDLK_d,
		 l = SDLK_a,
		 u = SDLK_w,
		 d = SDLK_s;

	auto move = 
		(disp->keyDown(r) ? Player::Right : 0) |
		(disp->keyDown(l) ? Player::Left  : 0);

	if (move != Player::MoveX)
		if ((player->move() & Player::MoveX) != move)
		{
			if (move)
				playerMove(player, move);
			else
				playerStop(player, Player::MoveX);
		}

	move =
		(disp->keyDown(d) ? Player::Down : 0) |
		(disp->keyDown(u) ? Player::Up   : 0);

	if (move != Player::MoveY)
		if ((player->move() & Player::MoveY) != move)
		{
			if (move)
				playerMove(player, move);
			else
				playerStop(player, Player::MoveY);
		}

	auto mouse = disp->mouse() + camera;
	auto rot = (mouse - player->position()).rotation();
	playerTurn(player, rot);
}

// networking commands go here
void Input::playerMove (Player* p, Player::Move m)
{
	p->move(m);
}
void Input::playerStop (Player* p, Player::Move m)
{
	p->stop(m);
}
void Input::playerTurn (Player* p, float rot)
{
	p->turn(rot, true);
}
