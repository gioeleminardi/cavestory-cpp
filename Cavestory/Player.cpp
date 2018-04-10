#include "Player.h"
#include "Graphics.h"

Player::Player()
{
}

Player::Player(Graphics & graphics, int x, int y) :
	AnimatedSprite(graphics, ".//content//sprites//MyChar.png", 0, 0, 16, 16, x, y, 100)
{
	this->SetupAnimations();
	this->PlayAnimation("RunRight");
}

Player::~Player()
{
}

void Player::Draw(Graphics & graphics)
{
	AnimatedSprite::Draw(graphics, this->_x, this->_y);
}

void Player::Update(float elapsedTime)
{
	AnimatedSprite::Update(elapsedTime);
}

void Player::MoveLeft()
{
}

void Player::MoveRight()
{
}

void Player::StopMoving()
{
}

void Player::AnimationDone(std::string currentAnimation)
{
}

void Player::SetupAnimations()
{
	Vector2 v;
	this->AddAnimation(1, 0, 0, "IdleLeft", 16, 16, v.zero());
	this->AddAnimation(1, 0, 16, "IdleRight", 16, 16, v.zero());
	this->AddAnimation(3, 0, 0, "RunLeft", 16, 16, v.zero());
	this->AddAnimation(3, 0, 16, "RunRight", 16, 16, v.zero());
}
