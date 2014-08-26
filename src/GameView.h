#pragma once

#include "Display.h"
#include "Game.h"



class GameView
	: public View
{
public:
	GameView ();
	virtual ~GameView ();

	virtual void update (Display* disp, double dt);
	virtual void draw (Display* disp);


	void positionCamera (Display* d, Player* p);

private:
	Game* _game;
	vec2f _camera;
	bool _cameraInit;

	vec2f _raycast;
};
