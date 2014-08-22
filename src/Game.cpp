#include "include.h"
#include "Game.h"
#include "Player.h"


Game::Game ()
	: _input(this)
{
	_players.emplace_back(vec2f(100, 100));
}

Game::~Game ()
{
}


Player* Game::userPlayer ()
{
	if (_players.empty())
		return nullptr;
	else // TODO: not this.
		return &_players.front();
}




void Game::updateInput (Display* disp, float dt) { _input.update(disp, dt); }


void Game::update (float dt)
{
	for (auto& p : _players)
		p.update(this, dt);

	// TODO: crazy things
}


