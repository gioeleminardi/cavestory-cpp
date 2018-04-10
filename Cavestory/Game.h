#pragma once

#include "Sprite.h"

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

	Sprite _player;
	
};

