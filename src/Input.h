#pragma once
#include "Player.h"

class Game;
class Display;


class Input
{
public:
	explicit Input (Game* game);
	
	// actions
	void update (Display* disp, const vec2f& cam, double dt);


	void playerMove (Player* p, Player::Move m);
	void playerStop (Player* p, Player::Move m);
	void playerTurn (Player* p, float rot);
private:
	Game* _game;
};
