#include "player.h"

namespace PLAYER 
{
	const std::string SPRITESHEET_PATH = "assets/player.png";
	const int WIDTH = 48;
	const int HEIGHT = 48;
	const float WALK_SPEED = 1.5f;

	const std::string ANIM_RUN_DOWN = "RunDown";
	const std::string ANIM_RUN_LEFT = "RunLeft";
	const std::string ANIM_RUN_UP = "RunUp";
	const std::string ANIM_RUN_RIGHT = "RunRight";
	const std::string ANIM_IDLE_DOWN = "IdleDown";
	const std::string ANIM_IDLE_LEFT = "IdleLeft";
	const std::string ANIM_IDLE_UP= "IdleUp";
	const std::string ANIM_IDLE_RIGHT = "IdleRight";
}

Player::Player() {}

Player::Player(Vector2 aSpawnPoint) :
	AnimatedSprite(PLAYER::SPRITESHEET_PATH, 0, 0, PLAYER::WIDTH, PLAYER::HEIGHT, aSpawnPoint, 0.15f)
{
	mDirection = { 0, 0 };
	setupAnimations();
	playAnimation(PLAYER::ANIM_IDLE_RIGHT);
}

void Player::setupAnimations() 
{
	addAnimation(4, false, 0, 0, PLAYER::ANIM_RUN_DOWN, PLAYER::WIDTH, PLAYER::HEIGHT);
	addAnimation(4, false, PLAYER::WIDTH, 0, PLAYER::ANIM_RUN_LEFT, PLAYER::WIDTH, PLAYER::HEIGHT);
	addAnimation(4, false, PLAYER::WIDTH * 2, 0, PLAYER::ANIM_RUN_UP, PLAYER::WIDTH, PLAYER::HEIGHT);
	addAnimation(4, false, PLAYER::WIDTH * 3, 0, PLAYER::ANIM_RUN_RIGHT, PLAYER::WIDTH, PLAYER::HEIGHT);

	addAnimation(1, false, 0, 0, PLAYER::ANIM_IDLE_DOWN, PLAYER::WIDTH, PLAYER::HEIGHT);
	addAnimation(1, false, PLAYER::WIDTH, 0, PLAYER::ANIM_IDLE_LEFT, PLAYER::WIDTH, PLAYER::HEIGHT);
	addAnimation(1, false, PLAYER::WIDTH * 2, 0, PLAYER::ANIM_IDLE_UP, PLAYER::WIDTH, PLAYER::HEIGHT);
	addAnimation(1, false, PLAYER::WIDTH * 3, 0, PLAYER::ANIM_IDLE_RIGHT, PLAYER::WIDTH, PLAYER::HEIGHT);
}

void Player::moveLeft() 
{
	mDirection.x = -PLAYER::WALK_SPEED;
	mDirection.y = 0;
	playAnimation(PLAYER::ANIM_RUN_LEFT);
	mFacing = LEFT;
}

void Player::moveRight() 
{
	mDirection.x = PLAYER::WALK_SPEED;
	mDirection.y = 0;
	playAnimation(PLAYER::ANIM_RUN_RIGHT);
	mFacing = RIGHT;
}

void Player::moveUp()
{
	mDirection.y = -PLAYER::WALK_SPEED;
	mDirection.x = 0;
	playAnimation(PLAYER::ANIM_RUN_UP);
	mFacing = UP;
}

void Player::moveDown() 
{
	mDirection.y = PLAYER::WALK_SPEED;
	mDirection.x = 0;
	playAnimation(PLAYER::ANIM_RUN_DOWN);
	mFacing = DOWN;
}

void Player::stopMoving() 
{
	mDirection.x = 0.0f;
	mDirection.y = 0.0f;

	switch (mFacing) {
	case LEFT:
		playAnimation(PLAYER::ANIM_IDLE_LEFT);
		break;
	case RIGHT:
		playAnimation(PLAYER::ANIM_IDLE_RIGHT);
		break;
	case UP:
		playAnimation(PLAYER::ANIM_IDLE_UP);
		break;
	case DOWN:
		playAnimation(PLAYER::ANIM_IDLE_DOWN);
		break;
	}
}

void Player::draw() 
{
	AnimatedSprite::draw(mPosition);
}

void Player::update(float aFrameTime) 
{
	mPosition.x += mDirection.x;
	mPosition.y += mDirection.y;

	AnimatedSprite::update(aFrameTime);
}

