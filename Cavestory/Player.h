#pragma once
#include "AnimatedSprite.h"

class Graphics;

class Player : public AnimatedSprite
{
public:
	Player();
	Player(Graphics &graphics, int x, int y);
	virtual ~Player();

	void Draw(Graphics &graphics);
	void Update(float ElapsedTime);

	virtual void AnimationDone(std::string currentAnimation) override;
	virtual void SetupAnimations() override;
};

