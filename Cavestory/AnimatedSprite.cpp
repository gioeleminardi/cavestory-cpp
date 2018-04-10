#include "AnimatedSprite.h"
#include "Graphics.h"

AnimatedSprite::AnimatedSprite()
{
}

AnimatedSprite::AnimatedSprite(Graphics & graphics, const std::string & filePath, int sourceX, int sourceY, int width, int height, int posX, int posY, float timeToUpdate) :
	Sprite(graphics, filePath, sourceX, sourceY, width, height, posX, posY),
	_frameIndex(0),
	_timeElapsed(0),
	_visible(true),
	_timeToUpdate(timeToUpdate),
	_currentAnimation(""),
	_currentAnimationOnce(false)
{

}

AnimatedSprite::~AnimatedSprite()
{
}

void AnimatedSprite::PlayAnimation(std::string animation, bool once)
{
}

void AnimatedSprite::Update(int elapsedTime)
{
}

void AnimatedSprite::Draw(Graphics & graphics, int x, int y)
{
}

void AnimatedSprite::SetupAnimations()
{
}

void AnimatedSprite::AddAnimation(int frames, int x, int y, std::string name, int width, int height, Vector2 offset)
{

}

void AnimatedSprite::ResetAnimations()
{
}

void AnimatedSprite::StopAnimation()
{
}

void AnimatedSprite::SetVisible(bool visible)
{
}

void AnimatedSprite::AnimationDone(std::string currentAnimation)
{
}
