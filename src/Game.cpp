#include "include.h"
#include "Game.h"
#include "Player.h"


Game::Game ()
	: _input(this)
{
	const int mapw = 3000;
	const int maph = 2000;
	const int nodes = 100;

	_players.emplace_back(vec2f(100, 100));

	_map.reserve(nodes);
	for (auto i = 0; i < nodes; i++)
		_map.emplace_back(math::random(mapw),
				          math::random(maph));
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



