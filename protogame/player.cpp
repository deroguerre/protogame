#include "player.h"

namespace PLAYER
{
	const std::string SPRITESHEET_PATH = "assets/player.png";
	const int WIDTH = 48;
	const int HEIGHT = 48;
	const float WALK_SPEED = 2.0f;

	const std::string ANIM_RUN_DOWN = "RunDown";
	const std::string ANIM_RUN_LEFT = "RunLeft";
	const std::string ANIM_RUN_UP = "RunUp";
	const std::string ANIM_RUN_RIGHT = "RunRight";
	const std::string ANIM_IDLE_DOWN = "IdleDown";
	const std::string ANIM_IDLE_LEFT = "IdleLeft";
	const std::string ANIM_IDLE_UP = "IdleUp";
	const std::string ANIM_IDLE_RIGHT = "IdleRight";
}

Player::Player() {}

Player::Player(Vector2 aSpawnPoint) :
	AnimatedSprite(PLAYER::SPRITESHEET_PATH, 0, 0, PLAYER::WIDTH, PLAYER::HEIGHT, aSpawnPoint, PLAYER::WALK_SPEED / 15.0f)
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
	//mDirection.x = -PLAYER::WALK_SPEED;
	playAnimation(PLAYER::ANIM_RUN_LEFT);
	mFacing = LEFT;
}

void Player::moveRight()
{
	//mDirection.x = PLAYER::WALK_SPEED;
	playAnimation(PLAYER::ANIM_RUN_RIGHT);
	mFacing = RIGHT;
}

void Player::moveUp()
{
	//mDirection.y = -PLAYER::WALK_SPEED;
	playAnimation(PLAYER::ANIM_RUN_UP);
	mFacing = UP;
}

void Player::moveDown()
{
	//mDirection.y = PLAYER::WALK_SPEED;
	playAnimation(PLAYER::ANIM_RUN_DOWN);
	mFacing = DOWN;
}

void Player::stopMoving()
{
	//mDirection.x = 0.0f;
	//mDirection.y = 0.0f;

	switch (mFacing) {
	case UP:
		playAnimation(PLAYER::ANIM_IDLE_UP);
		break;
	case DOWN:
		playAnimation(PLAYER::ANIM_IDLE_DOWN);
		break;
	case LEFT:
		playAnimation(PLAYER::ANIM_IDLE_LEFT);
		break;
	case RIGHT:
		playAnimation(PLAYER::ANIM_IDLE_RIGHT);
		break;
	}
}

void Player::handleTileCollisions(std::vector<Rectangle> aOthersRects) {

	for (int i = 0; i < aOthersRects.size(); i++) {
		sides::Side lCollisionSide = Sprite::getCollisionSide(aOthersRects.at(i));
		if (lCollisionSide != sides::NONE) {
			switch (lCollisionSide) {
			case sides::TOP: //Player Top side
				mPosition.y = aOthersRects.at(i).y + aOthersRects.at(i).height + 1;
				break;
			case sides::BOTTOM: //Player Bottom side
				mPosition.y = aOthersRects.at(i).y - getCollisionRect().height - 1;
				break;
			case sides::LEFT: //Player Left side
				mPosition.x = aOthersRects.at(i).x + aOthersRects.at(i).width + 1;
				break;
			case sides::RIGHT: //Player Right side
				mPosition.x = aOthersRects.at(i).x - getCollisionRect().width - 1;
				break;
			}

		}
	}

}

void Player::draw()
{
	AnimatedSprite::draw(mPosition);
}

void Player::update(float aFrameTime)
{

	// Controls
	//--------------------------------------------------------------------------------------

	//binding animation
	if (IsKeyDown(KEY_A) && IsKeyUp(KEY_W) && IsKeyUp(KEY_S)) {
		this->moveLeft();
	}
	else if (IsKeyDown(KEY_D) && IsKeyUp(KEY_W) && IsKeyUp(KEY_S)) {
		this->moveRight();
	}
	else if (IsKeyDown(KEY_W)) {
		this->moveUp();
	}
	else if (IsKeyDown(KEY_S)) {
		this->moveDown();
	}
	else
		this->stopMoving();

	//prevent opponents keys animation
	//(left and right)
	if (IsKeyDown(KEY_A) && IsKeyDown(KEY_D) && IsKeyUp(KEY_W) && IsKeyUp(KEY_S)) {
		this->stopMoving();
	}
	//(up and down)
	if (IsKeyDown(KEY_W) && IsKeyDown(KEY_S) && IsKeyUp(KEY_A) && IsKeyUp(KEY_D)) {
		this->stopMoving();
	}

	//prevent all keys press animation
	if (IsKeyDown(KEY_W) && IsKeyDown(KEY_S) && IsKeyDown(KEY_A) && IsKeyDown(KEY_D)) {
		this->stopMoving();
	}

	//movement
	if (IsKeyDown(KEY_A))
		mPosition.x += -PLAYER::WALK_SPEED;
	if (IsKeyDown(KEY_D))
		mPosition.x += PLAYER::WALK_SPEED;
	if (IsKeyDown(KEY_W))
		mPosition.y += -PLAYER::WALK_SPEED;
	if (IsKeyDown(KEY_S))
		mPosition.y += PLAYER::WALK_SPEED;

	//--------------------------------------------------------------------------------------

	AnimatedSprite::update(aFrameTime);
}
