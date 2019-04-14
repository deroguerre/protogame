#include "Player.h"

namespace PLAYER {
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

#pragma region Player movements

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

void Player::stopMoving() {

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

#pragma endregion

#pragma region Player collisions

void Player::handleTileCollisions(std::vector<Rectangle> aOthersRects) {

	std::vector<Rectangle> lCollisions;
	for (auto lTile : aOthersRects)
		if (CheckCollisionRecs(getCollisionRect(), lTile))
			lCollisions.push_back(lTile);
	
	if (!lCollisions.empty()) {
		for (auto lCollision : lCollisions) {
			Sides::Side lCollisionSide = Sprite::getCollisionSide(lCollision);
			if (lCollisionSide != Sides::NONE) {
				switch (lCollisionSide) {
				case Sides::TOP: //Player Top side
					mPosition.y = lCollision.y + lCollision.height + 1;
					break;
				case Sides::BOTTOM: //Player Bottom side
					mPosition.y = lCollision.y - getCollisionRect().height - 1;
					break;
				case Sides::LEFT: //Player Left side
					mPosition.x = lCollision.x + lCollision.width + 1;
					break;
				case Sides::RIGHT: //Player Right side
					mPosition.x = lCollision.x - getCollisionRect().width - 1;
					break;
				}
			}
		}
	}
}

void Player::handleDoorCollisions(Level* aLevel) {
	std::vector<Rectangle> lDoors = aLevel->getCurrentRoom()->getCollisionDoors();

	std::vector<Rectangle> lCollisions;
	for (auto lDoor : lDoors)
		if (CheckCollisionRecs(getCollisionRect(), lDoor))
			lCollisions.push_back(lDoor);

	if (!lCollisions.empty()) {
		for (auto lCollison : lCollisions) {
			Sides::Side lCollisionSide = Sprite::getCollisionSide(lCollison);
			if (lCollisionSide != Sides::NONE) {
				Vector2 lSpawn;
				switch (lCollisionSide) {
				case Sides::TOP: //Player Top side
					aLevel->nextRoom(ROOM_DOOR_TOP);
					lSpawn = aLevel->getCurrentRoom()->getPlayerSpawn(ROOM_DOOR_BOTTOM);
					setPosition({lSpawn.x - PLAYER::WIDTH / 2, lSpawn.y - PLAYER::HEIGHT});
					break;
				case Sides::BOTTOM: //Player Bottom side
					aLevel->nextRoom(ROOM_DOOR_BOTTOM);
					lSpawn = aLevel->getCurrentRoom()->getPlayerSpawn(ROOM_DOOR_TOP);
					setPosition({ lSpawn.x - PLAYER::WIDTH / 2, lSpawn.y});
					break;
				case Sides::LEFT: //Player Left side
					aLevel->nextRoom(ROOM_DOOR_LEFT);
					lSpawn = aLevel->getCurrentRoom()->getPlayerSpawn(ROOM_DOOR_RIGHT);
					setPosition({ lSpawn.x - PLAYER::WIDTH, lSpawn.y - PLAYER::HEIGHT / 2 });
					break;
				case Sides::RIGHT: //Player Right side
					aLevel->nextRoom(ROOM_DOOR_RIGHT);
					lSpawn = aLevel->getCurrentRoom()->getPlayerSpawn(ROOM_DOOR_LEFT);
					setPosition({ lSpawn.x, lSpawn.y - PLAYER::HEIGHT / 2 });
					break;
				}
			}
		}
	}
}

#pragma endregion

void Player::update(float aFrameTime) {
	// Controls
	//--------------------------------------------------------------------------------------

	//binding animation
	if (IsKeyDown(KEY_A) && IsKeyUp(KEY_W) && IsKeyUp(KEY_S))
		moveLeft();
	else if (IsKeyDown(KEY_D) && IsKeyUp(KEY_W) && IsKeyUp(KEY_S))
		moveRight();
	else if (IsKeyDown(KEY_W))
		moveUp();
	else if (IsKeyDown(KEY_S))
		moveDown();
	else
		stopMoving();

	//prevent opponents keys animation
	//(left and right)
	if (IsKeyDown(KEY_A) && IsKeyDown(KEY_D) && IsKeyUp(KEY_W) && IsKeyUp(KEY_S))
		stopMoving();

	//(up and down)
	if (IsKeyDown(KEY_W) && IsKeyDown(KEY_S) && IsKeyUp(KEY_A) && IsKeyUp(KEY_D))
		stopMoving();

	//prevent all keys press animation
	if (IsKeyDown(KEY_W) && IsKeyDown(KEY_S) && IsKeyDown(KEY_A) && IsKeyDown(KEY_D))
		stopMoving();

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

void Player::draw()
{
	AnimatedSprite::draw(mPosition);
}


