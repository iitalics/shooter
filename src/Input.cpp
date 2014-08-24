#include "include.h"
#include "Game.h"
#include "Display.h"


Input::Input (Game* game)
	: _game(game)
{ }


void Input::update (Display* disp, float dt)
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
				player->move(move);
			else
				player->stop(Player::MoveX);
		}

	move =
		(disp->keyDown(d) ? Player::Down : 0) |
		(disp->keyDown(u) ? Player::Up   : 0);

	if (move != Player::MoveY)
		if ((player->move() & Player::MoveY) != move)
		{
			if (move)
				player->move(move);
			else
				player->stop(Player::MoveY);
		}
}
