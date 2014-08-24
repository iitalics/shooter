#include "include.h"
#include "GameView.h"
#include "Game.h"
#include "Player.h"
#include "Map.h"


GameView::GameView ()
	: _game(),
	  _cameraInit(false)
{ }

GameView::~GameView () {}



void GameView::update (Display* disp, double dt)
{
	_game.updateInput(disp, _camera, dt);
	_game.update(dt);

	auto p = _game.userPlayer();
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

	_game.map()->draw(disp, _camera);

	for (auto& p : _game.players())
		p.draw();

	glPopMatrix();
}

void GameView::positionCamera (Display* disp, Player* p)
{
	auto w = disp->width();
	auto h = disp->height();
	auto pos = p->position();
	auto pad = .4f;

	rect box { 
		.x = w * pad + _camera.x,
		.y = h * pad + _camera.y,
		.width = w * (1 - pad - pad),
		.height = h * (1 - pad - pad) };

	auto dest = _camera;

	if (pos.x < box.x)
		dest.x += pos.x - box.x;
	else if (pos.x > box.right())
		dest.x += pos.x - box.right();
	
	if (pos.y < box.y)
		dest.y += pos.y - box.y;
	else if (pos.y > box.bottom())
		dest.y += pos.y - box.bottom();

	_camera = math::lerp(.1f,
					_camera, dest);
}


