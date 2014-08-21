#pragma once

#include "Display.h"
#include "Game.h"


class GameView
	: public View
{
public:
	GameView ();
	virtual ~GameView ();

	virtual void update (Display* disp, float dt);
	virtual void draw (Display* disp);


private:
	Game _game;
};
