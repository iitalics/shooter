#include "include.h"
#include "Game.h"
#include "Player.h"
#include "Map.h"


Game::Game ()
	: _input(this),
	  _world(new b2World({ 0, 0 })),
	  _map(new Map())
{
	_players.push_back(Player(this, _map->size() / 2));
}

Game::~Game ()
{ }



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

	_world->Step(float(dt), 1, 1);
}



void Game::drawOverlay (Display* disp)
{
}


