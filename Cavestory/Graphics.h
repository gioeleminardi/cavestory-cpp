/* Graphics.cpp
* This class manage graphics
*
*/
#pragma once
#include <string>
#include <map>

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Surface;
struct SDL_Texture;
struct SDL_Rect;

class Graphics
{
public:
	Graphics();
	virtual ~Graphics();

	/* SDL_Surface* loadImage
		Loads image from disk
	*/
	SDL_Surface* LoadSurfaceImage(const std::string &filePath);

	/* void blitSurface
		Draw a texture to a certain part of the screen
	*/
	void BlitSurface(SDL_Texture *texture, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle);

	/* void flip
		Renders everything to the screen
	*/
	void Flip();

	/* void clear
		Clears the screen
	*/
	void Clear();

	SDL_Renderer* GetRenderer() const;
private:
	SDL_Window * _window;
	SDL_Renderer* _renderer;

	std::map<std::string, SDL_Surface*> _spriteSheets;
};

