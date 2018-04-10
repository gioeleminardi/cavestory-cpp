#pragma once
#include "Sprite.h"
#include "Globals.h"

#include <string>
#include <map>
#include <vector>

class Graphics;

/* AnimatedSprite
	Holds Logic for animating sprites
*/
class AnimatedSprite :  public Sprite
{
public:
	AnimatedSprite();
	AnimatedSprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height,
		int posX, int posY, float TimeToUpdate);
	virtual ~AnimatedSprite();

	// Play animation if it's not already playing
	void PlayAnimation(std::string animation, bool once = false);

	// Updates the animated sprite (timer)
	void Update(int elapsedTime);

	// Draws the sprite to the screen
	void Draw(Graphics &graphics, int x, int y);

	// Sets up all animations for a sprite
	virtual void SetupAnimations();

private:
	std::map<std::string, std::vector<SDL_Rect>> _animations;
};

