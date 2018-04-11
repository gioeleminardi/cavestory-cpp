#pragma once

#include "Globals.h"
#include <string>

class Graphics;
struct SDL_Texture;

class Level
{
public:
	Level();
	Level(std::string mapName, Vector2 spawnPoint, Graphics &graphics);
	virtual ~Level();
	void Update(float elapsedTime);
	void Draw(Graphics &graphics);

private:
	std::string _mapName;
	Vector2 _spawnPoint;
	Vector2 _size;

	SDL_Texture* _backgroundTexture;

	void LoadMap(std::string mapName, Graphics &graphics);
};