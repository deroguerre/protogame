#include "Player.h"

namespace PLAYER {
	const std::string SPRITESHEET_PATH = "assets/django.png";
	const int WIDTH = 32;
	const int HEIGHT = 48;
	const float WALK_SPEED = 2.3f;

	//IDLE UP-DOWN-LEFT-RIGHT
	const std::string ANIM_IDLE_DOWN = "IdleDown";
	const std::string ANIM_IDLE_LEFT = "IdleLeft";
	const std::string ANIM_IDLE_UP = "IdleUp";
	const std::string ANIM_IDLE_RIGHT = "IdleRight";
	//IDLE DIAGONAL
	const std::string ANIM_IDLE_UPLEFT = "IdleUpLeft";
	const std::string ANIM_IDLE_UPRIGHT = "IdleUpRight";
	const std::string ANIM_IDLE_DOWNLEFT = "IdleDownLeft";
	const std::string ANIM_IDLE_DOWNRIGHT = "IdleDownRight";

	//RUN UP-DOWN-LEFT-RIGHT
	const std::string ANIM_RUN_DOWN = "RunDown";
	const std::string ANIM_RUN_LEFT = "RunLeft";
	const std::string ANIM_RUN_UP = "RunUp";
	const std::string ANIM_RUN_RIGHT = "RunRight";
	//RUN DIAGONAL
	const const std::string ANIM_RUN_UPLEFT = "RunUpLeft";
	const const std::string ANIM_RUN_UPRIGHT = "RunUPRight";
	const const std::string ANIM_RUN_DOWNLEFT = "RunDownLeft";
	const const std::string ANIM_RUN_DOWNRIGHT = "RunDownRight";
}

Player::Player() {}

Player::Player(Vector2 aSpawnPoint) :
	AnimatedSprite(PLAYER::SPRITESHEET_PATH, 0, 0, PLAYER::WIDTH, PLAYER::HEIGHT, aSpawnPoint, PLAYER::WALK_SPEED / 25.0f)
{
	mDirection = { 0, 0 };
	setupAnimations();
	playAnimation(PLAYER::ANIM_IDLE_RIGHT);
}

void Player::setupAnimations()
{
	//IDLE UP-DOWN-LEFT-RIGHT
	addAnimation(1, true, 0, 0, PLAYER::ANIM_IDLE_UP, PLAYER::WIDTH, PLAYER::HEIGHT);
	addAnimation(1, true, 0, PLAYER::HEIGHT * 4, PLAYER::ANIM_IDLE_DOWN, PLAYER::WIDTH, PLAYER::HEIGHT);
	addAnimation(1, true, 0, PLAYER::HEIGHT * 6, PLAYER::ANIM_IDLE_LEFT, PLAYER::WIDTH, PLAYER::HEIGHT);
	addAnimation(1, true, 0, PLAYER::HEIGHT * 2, PLAYER::ANIM_IDLE_RIGHT, PLAYER::WIDTH, PLAYER::HEIGHT);

	//IDLE DIAGOLNAL
	addAnimation(1, true, 0, PLAYER::HEIGHT  * 7, PLAYER::ANIM_IDLE_UPLEFT, PLAYER::WIDTH, PLAYER::HEIGHT);
	addAnimation(1, true, 0, PLAYER::HEIGHT, PLAYER::ANIM_IDLE_UPRIGHT, PLAYER::WIDTH, PLAYER::HEIGHT);
	addAnimation(1, true, 0, PLAYER::HEIGHT * 5, PLAYER::ANIM_IDLE_DOWNLEFT, PLAYER::WIDTH, PLAYER::HEIGHT);
	addAnimation(1, true, 0, PLAYER::HEIGHT * 3, PLAYER::ANIM_IDLE_DOWNRIGHT, PLAYER::WIDTH, PLAYER::HEIGHT);

	//WALK UP-DOWN-LEFT-RIGHT
	addAnimation(8, true, 0, PLAYER::HEIGHT * 8, PLAYER::ANIM_RUN_UP, PLAYER::WIDTH, PLAYER::HEIGHT);
	addAnimation(8, true, 0, PLAYER::HEIGHT * 12, PLAYER::ANIM_RUN_DOWN, PLAYER::WIDTH, PLAYER::HEIGHT);
	addAnimation(8, true, 0, PLAYER::HEIGHT * 14, PLAYER::ANIM_RUN_LEFT, PLAYER::WIDTH, PLAYER::HEIGHT);
	addAnimation(8, true, 0, PLAYER::HEIGHT * 10, PLAYER::ANIM_RUN_RIGHT, PLAYER::WIDTH, PLAYER::HEIGHT);

	//WALK DIAGOLNAL
	addAnimation(8, true, 0, PLAYER::HEIGHT * 13, PLAYER::ANIM_RUN_DOWNLEFT, PLAYER::WIDTH, PLAYER::HEIGHT);
	addAnimation(8, true, 0, PLAYER::HEIGHT * 11, PLAYER::ANIM_RUN_DOWNRIGHT, PLAYER::WIDTH, PLAYER::HEIGHT);
	addAnimation(8, true, 0, PLAYER::HEIGHT * 15, PLAYER::ANIM_RUN_UPLEFT, PLAYER::WIDTH, PLAYER::HEIGHT);
	addAnimation(8, true, 0, PLAYER::HEIGHT * 9, PLAYER::ANIM_RUN_UPRIGHT, PLAYER::WIDTH, PLAYER::HEIGHT);
}

#pragma region Player movements

void Player::moveUp() {
	playAnimation(PLAYER::ANIM_RUN_UP);
	mFacing = UP;
}

void Player::moveDown() {
	//mDirection.y = PLAYER::WALK_SPEED;
	playAnimation(PLAYER::ANIM_RUN_DOWN);
	mFacing = DOWN;
}

void Player::moveLeft() {
	playAnimation(PLAYER::ANIM_RUN_LEFT);
	mFacing = LEFT;
}

void Player::moveRight() {
	playAnimation(PLAYER::ANIM_RUN_RIGHT);
	mFacing = RIGHT;
}

void Player::moveUpLeft() {
	playAnimation(PLAYER::ANIM_RUN_UPLEFT);
	mFacing = UPLEFT;
}

void Player::moveUpRight() {
	playAnimation(PLAYER::ANIM_RUN_UPRIGHT);
	mFacing = UPRIGHT;
}

void Player::moveDownLeft() {
	playAnimation(PLAYER::ANIM_RUN_DOWNLEFT);
	mFacing = DOWNLEFT;
}

void Player::moveDownRight() {
	playAnimation(PLAYER::ANIM_RUN_DOWNRIGHT);
	mFacing = DOWNRIGHT;
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
	case UPLEFT:
		playAnimation(PLAYER::ANIM_IDLE_UPLEFT);
		break;
	case UPRIGHT:
		playAnimation(PLAYER::ANIM_IDLE_UPRIGHT);
		break;
	case DOWNLEFT:
		playAnimation(PLAYER::ANIM_IDLE_DOWN);
		break;
	case DOWNRIGHT:
		playAnimation(PLAYER::ANIM_IDLE_DOWN);
		break;
	}
}

#pragma endregion

#pragma region Player collisions

void Player::handleTileCollisions(std::vector<Rectangle> aOthersRects) {

	std::vector<Rectangle> lCollisions;
	for (auto lTile : aOthersRects) {
		if (CheckCollisionRecs(Sprite::getCollisionRect(), lTile)) {
			lCollisions.push_back(lTile);
		}
	}
	
	if (!lCollisions.empty()) {
		for (auto lCollision : lCollisions) {
			Sides::Side lCollisionSide = Sprite::getCollisionSide(lCollision);
			if (lCollisionSide != Sides::NONE) {
				switch (lCollisionSide) {
				case Sides::TOP: //Player Top side
					mPosition.y = lCollision.y + lCollision.height + 1;
					break;
				case Sides::BOTTOM: //Player Bottom side
					mPosition.y = lCollision.y - Sprite::getCollisionRect().height - 1;
					break;
				case Sides::LEFT: //Player Left side
					mPosition.x = lCollision.x + lCollision.width + 1;
					break;
				case Sides::RIGHT: //Player Right side
					mPosition.x = lCollision.x - Sprite::getCollisionRect().width - 1;
					break;
				}
			}
		}
	}
}

void Player::handleDoorCollisions(Level* aLevel) {}

//void Player::handleDoorCollisions(Level* aLevel) {
//	std::vector<Rectangle> lDoors = aLevel->getCurrentRoom()->getCollisionDoors();
//
//	std::vector<Rectangle> lCollisions;
//	for (auto lDoor : lDoors)
//		if (CheckCollisionRecs(getCollisionRect(), lDoor))
//			lCollisions.push_back(lDoor);
//
//	if (!lCollisions.empty()) {
//		for (auto lCollison : lCollisions) {
//			Sides::Side lCollisionSide = Sprite::getCollisionSide(lCollison);
//			if (lCollisionSide != Sides::NONE) {
//				Vector2 lSpawn;
//				switch (lCollisionSide) {
//				case Sides::TOP: //Player Top side
//					aLevel->nextRoom(ROOM_DOOR_TOP);
//					lSpawn = aLevel->getCurrentRoom()->getPlayerSpawn(ROOM_DOOR_BOTTOM);
//					setPosition({lSpawn.x - PLAYER::WIDTH / 2, lSpawn.y - PLAYER::HEIGHT});
//					break;
//				case Sides::BOTTOM: //Player Bottom side
//					aLevel->nextRoom(ROOM_DOOR_BOTTOM);
//					lSpawn = aLevel->getCurrentRoom()->getPlayerSpawn(ROOM_DOOR_TOP);
//					setPosition({ lSpawn.x - PLAYER::WIDTH / 2, lSpawn.y});
//					break;
//				case Sides::LEFT: //Player Left side
//					aLevel->nextRoom(ROOM_DOOR_LEFT);
//					lSpawn = aLevel->getCurrentRoom()->getPlayerSpawn(ROOM_DOOR_RIGHT);
//					setPosition({ lSpawn.x - PLAYER::WIDTH, lSpawn.y - PLAYER::HEIGHT / 2 });
//					break;
//				case Sides::RIGHT: //Player Right side
//					aLevel->nextRoom(ROOM_DOOR_RIGHT);
//					lSpawn = aLevel->getCurrentRoom()->getPlayerSpawn(ROOM_DOOR_LEFT);
//					setPosition({ lSpawn.x, lSpawn.y - PLAYER::HEIGHT / 2 });
//					break;
//				}
//			}
//		}
//	}
//}

#pragma endregion

void Player::update(float aFrameTime) {

	// Controls
	//--------------------------------------------------------------------------------------

	if (IsKeyDown(KEY_W) && IsKeyUp(KEY_A) && IsKeyUp(KEY_S) && IsKeyUp(KEY_D))			//UP
		moveUp();
	else if (IsKeyDown(KEY_S) && IsKeyUp(KEY_A) && IsKeyUp(KEY_W) && IsKeyUp(KEY_D))	//DOWN
		moveDown();
	else if (IsKeyDown(KEY_A) && IsKeyUp(KEY_W) && IsKeyUp(KEY_S) && IsKeyUp(KEY_D))	//LEFT
		moveLeft();
	else if (IsKeyDown(KEY_D) && IsKeyUp(KEY_A) && IsKeyUp(KEY_W) && IsKeyUp(KEY_S))	//RIGHT
		moveRight();
	else if (IsKeyDown(KEY_W) && IsKeyDown(KEY_A) && IsKeyUp(KEY_S) && IsKeyUp(KEY_D))	//UP LEFT
		moveUpLeft();
	else if (IsKeyDown(KEY_W) && IsKeyDown(KEY_D) && IsKeyUp(KEY_A) && IsKeyUp(KEY_S))	//UP RIGHT
		moveUpRight();
	else if (IsKeyDown(KEY_S) && IsKeyDown(KEY_A) && IsKeyUp(KEY_W) && IsKeyUp(KEY_D))	//DOWN LEFT
		moveDownLeft();
	else if (IsKeyDown(KEY_S) && IsKeyDown(KEY_D) && IsKeyUp(KEY_A) && IsKeyUp(KEY_W))	//DOWN RIGHT
		moveDownRight();
	else if (IsKeyDown(KEY_W) && IsKeyDown(KEY_S) && IsKeyDown(KEY_A))					//UP DOWN LEFT
		moveLeft();
	else if (IsKeyDown(KEY_W) && IsKeyDown(KEY_S) && IsKeyDown(KEY_D))					//UP DOWN RIGHT
		moveRight();
	else if (IsKeyDown(KEY_A) && IsKeyDown(KEY_D) && IsKeyDown(KEY_S))					//LEFT RIGHT DOWN
		moveDown();
	else if (IsKeyDown(KEY_A) && IsKeyDown(KEY_D) && IsKeyDown(KEY_W))					//LEFT DOWN UP
		moveUp();
	else
		stopMoving();

	//prevent opponents keys animation
	if (IsKeyDown(KEY_A) && IsKeyDown(KEY_D) && IsKeyUp(KEY_W) && IsKeyUp(KEY_S)) 	//(left and right)
		stopMoving();
	if (IsKeyDown(KEY_W) && IsKeyDown(KEY_S) && IsKeyUp(KEY_A) && IsKeyUp(KEY_D)) 	//(up and down)
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


