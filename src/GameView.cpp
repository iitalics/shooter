#include "include.h"
#include "GameView.h"
#include "Game.h"
#include "Player.h"


GameView::GameView ()
{
}
GameView::~GameView () {}

void GameView::update (Display* disp, float dt)
{
	_game.update(dt);
}

void GameView::draw (Display* disp)
{
	color(0, 0, 0).glApplyClear();

	for (auto& p : _game.players())
		p.draw();
}
