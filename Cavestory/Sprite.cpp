#include "Sprite.h"
#include "Graphics.h"
#include "easylogging++.h"

Sprite::Sprite()
{
}

Sprite::Sprite(Graphics & graphics, const std::string & filePath, int sourceX, int sourceY, int width, int height, float posX, float posY) :
	_x(posX),
	_y(posY)
{
	this->_sourceRect.x = sourceX;
	this->_sourceRect.y = sourceY;
	this->_sourceRect.w = width;
	this->_sourceRect.h = height;

	this->_spriteSheet = SDL_CreateTextureFromSurface(graphics.GetRenderer(), graphics.LoadSurfaceImage(filePath));

	if (this->_spriteSheet == nullptr) {
		LOG(ERROR) << "Unable to load image: " << SDL_GetError();
	}
}

Sprite::~Sprite()
{
}

void Sprite::Update()
{
}

void Sprite::Draw(Graphics & graphics, int x, int y)
{
	SDL_Rect destinationRectangle = {
		x,
		y,
		this->_sourceRect.w,
		this->_sourceRect.h
	};

	graphics.BlitSurface(this->_spriteSheet, &this->_sourceRect, &destinationRectangle);
}
