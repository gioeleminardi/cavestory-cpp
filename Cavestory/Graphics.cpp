#include <SDL.h>
#include <SDL_image.h>
#include "Graphics.h"

Graphics::Graphics()
{
	SDL_CreateWindowAndRenderer(640, 480, 0, &this->_window, &this->_renderer);
	SDL_SetWindowTitle(this->_window, "Cavestory");
}

Graphics::~Graphics()
{
	SDL_DestroyWindow(this->_window);
}

SDL_Surface * Graphics::LoadSurfaceImage(const std::string & filePath)
{

	if (this->_spriteSheets.count(filePath) == 0) {
		this->_spriteSheets[filePath] = IMG_Load(filePath.c_str());
	}

	return this->_spriteSheets[filePath];
}

void Graphics::BlitSurface(SDL_Texture * texture, SDL_Rect * sourceRectangle, SDL_Rect * destinationRectangle)
{
	SDL_RenderCopy(this->_renderer, texture, sourceRectangle, destinationRectangle);
}

void Graphics::Flip()
{
	SDL_RenderPresent(this->_renderer);
}

void Graphics::Clear()
{
	SDL_RenderClear(this->_renderer);
}

SDL_Renderer * Graphics::GetRenderer() const
{
	return this->_renderer;
}
