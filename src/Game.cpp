#include "include.h"
#include "Game.h"
#include "Player.h"
#include "Map.h"


Game::Game ()
	: _input(this),
	  _map(new Map())
{
	_players.push_back(Player(vec2f()));
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




void Game::updateInput (Display* disp, const vec2f& cam, double dt)
{
	_input.update(disp, cam, dt);
}


void Game::update (double dt)
{
	for (auto& p : _players)
		p.update(this, dt);

	// TODO: crazy things
}


