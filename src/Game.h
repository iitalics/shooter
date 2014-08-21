#pragma once

class Player;

class Game
{
public:
	explicit Game ();
	~Game ();

	void update (float dt);

	std::vector<Player>& players () { return _players; }


private:

	std::vector<Player> _players;
};
