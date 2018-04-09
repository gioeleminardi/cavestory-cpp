/* Graphics.cpp
* This class manage graphics
*
*/
#pragma once

struct SDL_Window;
struct SDL_Renderer;

class Graphics
{
public:
	Graphics();
	virtual ~Graphics();
private:
	SDL_Window * _window;
	SDL_Renderer* _renderer;
};

