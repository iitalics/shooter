#include "include.h"
#include "GameView.h"
#include "Game.h"
#include "Player.h"
#include "Map.h"


GameView::GameView ()
	: _game(new Game()),
	  _cameraInit(false),
	  _raycast()
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

		FunctionCallback fn([&] (b2Fixture* fix,
					            const b2Vec2& pos,
								const b2Vec2& norm,
								float fraction)
				{
					_raycast.x = pos.x * Game::WorldScale;
					_raycast.y = pos.y * Game::WorldScale;
					return 0;
				});

		auto mouse = disp->mouse() + _camera;
		_raycast = mouse;
		_game->world()->RayCast(&fn,
				to_b2(p->position()),
				to_b2(mouse));
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

	auto player = _game->userPlayer();
	if (player)
	{
		color(1, 1, 0).gl();
		glBegin(GL_LINES);
		player->position().gl();
		_raycast.gl();
		glEnd();
	}

	glPopMatrix();

	_game->drawOverlay(disp);
}

void GameView::positionCamera (Display* disp, Player* p)
{
	/*auto w = disp->width(), h = disp->height();
	auto pos = p->position();
	auto pad = .4f;
	rect box { 
		w * pad + _camera.x,
		h * pad + _camera.y,
		w * (1 - pad - pad),
		h * (1 - pad - pad) };
	if (pos.x < box.x)
		dest.x += pos.x - box.x;
	else if (pos.x > box.right())
		dest.x += pos.x - box.right();
	if (pos.y < box.y)
		dest.y += pos.y - box.y;
	else if (pos.y > box.bottom())
		dest.y += pos.y - box.bottom(); */
	auto mouse = disp->mouse() + _camera;
	auto lookOffset = mouse - p->position();

	auto dest = p->position() - disp->size() / 2 +
					lookOffset * .12f;

	_camera = math::lerp(.2f,
					_camera, dest);
}


