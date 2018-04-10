#include "AnimatedSprite.h"
#include "Graphics.h"
#include "easylogging++.h"

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

void AnimatedSprite::Update(float elapsedTime)
{
	Sprite::Update();

	this->_timeElapsed += elapsedTime;
	//LOG(INFO) << "[AnimatedSprite::Update] _timeElapsed: " << this->_timeElapsed;
	if (this->_timeElapsed > this->_timeToUpdate) {
		//LOG(INFO) << "[AnimatedSprite::Update] _timeElapsed > _timeToUpdate";
		this->_timeElapsed -= this->_timeToUpdate;
		if (this->_frameIndex < this->_animations[this->_currentAnimation].size() - 1) {
			this->_frameIndex++;
		}
		else {
			if (this->_currentAnimationOnce) {
				this->SetVisible(false);
			}
			this->_frameIndex = 0;
			this->AnimationDone(this->_currentAnimation);
		}
	}
}

void AnimatedSprite::Draw(Graphics & graphics, int x, int y)
{
	if (this->_visible) {
		//LOG(INFO) << "[AnimatedSprite::Draw][Animation is visible]"; 
		SDL_Rect destinationRectangle;
		destinationRectangle.x = x + this->_offsets[this->_currentAnimation].x;
		destinationRectangle.y = y + this->_offsets[this->_currentAnimation].y;
		destinationRectangle.w = this->_sourceRect.w * Globals::SPRITE_SCALE;
		destinationRectangle.h = this->_sourceRect.h * Globals::SPRITE_SCALE;

		SDL_Rect sourceRectangle = this->_animations[this->_currentAnimation][this->_frameIndex];
		graphics.BlitSurface(this->_spriteSheet, &sourceRectangle, &destinationRectangle);
	}
}

//void AnimatedSprite::SetupAnimations()
//{
//	this->AddAnimation(3, 0, 0, "RunLeft", 16, 16, Vector2(0, 0));
//	this->AddAnimation(3, 0, 16, "RunRight", 16, 16, Vector2(0, 0));
//}

void AnimatedSprite::AddAnimation(int frames, int x, int y, std::string name, int width, int height, Vector2 offset)
{
	std::vector<SDL_Rect> rectangles;
	for (int i = 0; i < frames; i++)
	{
		SDL_Rect newRect = {
			(i + x) * width,
			y,
			width,
			height
		};

		rectangles.push_back(newRect);
	}

	this->_animations.insert(std::pair<std::string, std::vector<SDL_Rect>>(name, rectangles));
	this->_offsets.insert(std::pair<std::string, Vector2>(name, offset));
}

void AnimatedSprite::ResetAnimations()
{
	this->_animations.clear();
	this->_offsets.clear();
}

void AnimatedSprite::PlayAnimation(std::string animation, bool once)
{
	this->_currentAnimationOnce = once;
	if (this->_currentAnimation != animation) {
		this->_currentAnimation = animation;
		this->_frameIndex = 0;
	}
}

void AnimatedSprite::StopAnimation()
{
	this->_frameIndex = 0;
	this->AnimationDone(this->_currentAnimation);
}

void AnimatedSprite::SetVisible(bool visible)
{
	this->_visible = visible;
}
