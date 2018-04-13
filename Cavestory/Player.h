#ifndef PLAYER_H
#define PLAYER_H

#include "AnimatedSprite.h"
#include "Globals.h"

class Graphics;

class Player : public AnimatedSprite
{
public:
	Player();
	Player(Graphics &graphics, float x, float y);
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

#endif