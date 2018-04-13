#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Level.h"

class Graphics;

class Game
{
public:
	Game();
	virtual ~Game();
private:
	void GameLoop();
	void Draw(Graphics &graphics);
	void Update(float DeltaTime);

	Player _player;
	Level _level;
};

#endif