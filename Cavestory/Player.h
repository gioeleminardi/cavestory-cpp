#pragma once
#include "AnimatedSprite.h"
#include "Globals.h"

class Graphics;

class Player : public AnimatedSprite
{
public:
	Player();
	Player(Graphics &graphics, int x, int y);
	virtual ~Player();

	void Draw(Graphics &graphics);
	void Update(float ElapsedTime);

	void MoveLeft();
	void MoveRight();
	void StopMoving();

	virtual void AnimationDone(std::string currentAnimation) override;
	virtual void SetupAnimations() override;
private:
	float _dx, _dy;

	Direction _facing;
};

