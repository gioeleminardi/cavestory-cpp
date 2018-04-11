#pragma once
#include <string>
#include <SDL.h>

class Graphics;

/* Sprite class
	Holds all information for individual sprites
*/
class Sprite
{
public:
	Sprite();
	Sprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height,
		float posX, float posY);
	virtual ~Sprite();
	virtual void Update();
	void Draw(Graphics &graphics, int x, int y);
protected:
	SDL_Rect _sourceRect;
	SDL_Texture * _spriteSheet;
	float _x, _y;
};

