#include "include.h"
#include "Game.h"
#include "Player.h"


Game::Game ()
{
	_players.emplace_back(vec2f(100, 100));
}

Game::~Game ()
{
}



void Game::update (float dt)
{
}
