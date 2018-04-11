#include "Level.h"
#include "Graphics.h"
#include "SDL.h"

Level::Level()
{
}

Level::Level(std::string mapName, Vector2 spawnPoint, Graphics & graphics) :
	_mapName(mapName),
	_spawnPoint(spawnPoint),
	_size(Vector2().zero())
{
	this->LoadMap(mapName, graphics);
}

Level::~Level()
{
}

void Level::Update(float elapsedTime)
{

}

void Level::Draw(Graphics & graphics)
{
	//Draw the background
	SDL_Rect sourceRect = {
		0,
		0,
		64,
		64
	};

	SDL_Rect destRect;
	for (int x = 0; x < this->_size.x / sourceRect.w; x++)
	{
		for (int y = 0; y < this->_size.y / sourceRect.h; y++)
		{
			destRect.x = x * sourceRect.w;
			destRect.y = y * sourceRect.h;
			destRect.w = sourceRect.w;
			destRect.h = sourceRect.h;
			graphics.BlitSurface(this->_backgroundTexture, &sourceRect, &destRect);
		}
	}
}

void Level::LoadMap(std::string mapName, Graphics & graphics)
{
	//TEMPORARY CODE TO LOAD THE BACKGROUND
	this->_backgroundTexture = SDL_CreateTextureFromSurface(graphics.GetRenderer(),
		graphics.LoadSurfaceImage(".//content//backgrounds//bkBlue.png"));

	this->_size = Vector2(Globals::SCREEN_WIDTH * 2, Globals::SCREEN_HEIGHT * 2);
}
