#include "include.h"
#include "GameView.h"
#include "Game.h"
#include "Player.h"
#include "Map.h"


GameView::GameView ()
	: _game(new Game()),
	  _cameraInit(false)
{ }

GameView::~GameView ()
{
	delete _game;
}



void GameView::update (Display* disp, double dt)
{
	_game->updateInput(disp, _camera, dt);
	_game->update(dt);

	auto p = _game->userPlayer();
	if (p)
	{
		if (!_cameraInit)
			_camera = p->position() - disp->size() / 2;
		else
			positionCamera(disp, p);
		_cameraInit = true;
	}
	else
		_cameraInit = false;
}

void GameView::draw (Display* disp)
{
	color(0, 0, 0).glApplyClear();

	glPushMatrix();
	glTranslatef(-_camera.x, -_camera.y, 0);

	_game->map()->draw(disp, _camera);

	for (auto& p : _game->players())
		p.draw();

	glPopMatrix();

	_game->drawOverlay(disp);
}

void GameView::positionCamera (Display* disp, Player* p)
{
	/*
	auto w = disp->width();
	auto h = disp->height();
	auto pos = p->position();
	auto pad = .4f;

	rect box { 
		.x = w * pad + _camera.x,
		.y = h * pad + _camera.y,
		.width = w * (1 - pad - pad),
		.height = h * (1 - pad - pad) };

	if (pos.x < box.x)
		dest.x += pos.x - box.x;
	else if (pos.x > box.right())
		dest.x += pos.x - box.right();
	
	if (pos.y < box.y)
		dest.y += pos.y - box.y;
	else if (pos.y > box.bottom())
		dest.y += pos.y - box.bottom();
	*/
	auto mouse = disp->mouse() + _camera;
	auto lookOffset = mouse - p->position();

	auto dest = p->position() - disp->size() / 2 +
					lookOffset * .12f;

	_camera = math::lerp(.2f,
					_camera, dest);
}


