#include "Player.h"
#include "Graphics.h"
#include "easylogging++.h"

namespace PlayerConstants {
	constexpr float WALK_SPEED = 0.2f;
}

Player::Player()
{
}

Player::Player(Graphics & graphics, float x, float y) :
	AnimatedSprite(graphics, ".//content//sprites//MyChar.png", 0, 0, 16, 16, x, y, 100)
{
	this->SetupAnimations();
	this->PlayAnimation("IdleRight");
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
	this->_x += _dx * elapsedTime;
	//LOG(INFO) << "Player _x = " << this->_x;
	AnimatedSprite::Update(elapsedTime);
}

void Player::MoveLeft()
{
	this->_dx = -PlayerConstants::WALK_SPEED;
	this->PlayAnimation("RunLeft");
	this->_facing = LEFT;
}

void Player::MoveRight()
{
	this->_dx = PlayerConstants::WALK_SPEED;
	this->PlayAnimation("RunRight");
	this->_facing = RIGHT;
}

void Player::StopMoving()
{
	this->_dx = 0;
	switch (_facing)
	{
	case LEFT: {
		this->PlayAnimation("IdleLeft");
		break;
	}
	case RIGHT: {
		this->PlayAnimation("IdleRight");
		break;
	}
	default:
		break;
	}
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
