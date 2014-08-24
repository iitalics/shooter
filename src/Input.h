#pragma once
#include "Player.h"

class Game;
class Display;


class Input
{
public:
	explicit Input (Game* game);
	
	// actions
	void update (Display* disp, float dt);

private:
	Game* _game;
};
