#include "include.h"
#include "Game.h"
#include "Display.h"
#include "Player.h"


Input::Input (Game* game)
	: _game(game)
{ }


void Input::update (Display* disp, float dt)
{
	auto player = _game->userPlayer();
	const int speed = 50;

	if (player)
	{
		if (disp->keyPressed(SDLK_RIGHT))
			player->move(player->position() + vec2f { speed, 0 });
		
		if (disp->keyPressed(SDLK_LEFT))
			player->move(player->position() - vec2f { speed, 0 });
	}
}
