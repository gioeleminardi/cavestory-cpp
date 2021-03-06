#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include "Sprite.h"
#include "Globals.h"

#include <string>
#include <map>
#include <vector>

class Graphics;

/* AnimatedSprite
	Holds Logic for animating sprites
*/
class AnimatedSprite : public Sprite
{
public:
	AnimatedSprite();
	AnimatedSprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height,
		float posX, float posY, float timeToUpdate);
	virtual ~AnimatedSprite();

	// Play animation if it's not already playing
	void PlayAnimation(std::string animation, bool once = false);

	// Updates the animated sprite (timer)
	void Update(float elapsedTime);

	// Draws the sprite to the screen
	void Draw(Graphics &graphics, float x, float y);

protected:
	double _timeToUpdate;
	std::string _currentAnimation;
	bool _currentAnimationOnce;

	void AddAnimation(int frames, int x, int y, std::string name, int width, int height, Vector2 offset);

	void ResetAnimations();

	void StopAnimation();

	void SetVisible(bool visible);

	virtual void AnimationDone(std::string currentAnimation) = 0;

	// Sets up all animations for a sprite
	virtual void SetupAnimations() = 0;

private:
	std::map<std::string, std::vector<SDL_Rect>> _animations;
	std::map<std::string, Vector2> _offsets;

	int _frameIndex;
	double _timeElapsed;
	bool _visible;
};

#endif