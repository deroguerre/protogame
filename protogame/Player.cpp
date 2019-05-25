#include "Player.h"

namespace PLAYER {
	const std::string SPRITESHEET_PATH = "assets/django.png";
	const int WIDTH = 32;
	const int HEIGHT = 48;
	float WALK_SPEED = 2.3f;

	const std::string
		//IDLE UP-DOWN-LEFT-RIGHT
		ANIM_IDLE_DOWN = "IdleDown",
		ANIM_IDLE_LEFT = "IdleLeft",
		ANIM_IDLE_UP = "IdleUp",
		ANIM_IDLE_RIGHT = "IdleRight",

		//IDLE DIAGONAL
		ANIM_IDLE_UPLEFT = "IdleUpLeft",
		ANIM_IDLE_UPRIGHT = "IdleUpRight",
		ANIM_IDLE_DOWNLEFT = "IdleDownLeft",
		ANIM_IDLE_DOWNRIGHT = "IdleDownRight",

		//RUN UP-DOWN-LEFT-RIGHT
		ANIM_RUN_DOWN = "RunDown",
		ANIM_RUN_LEFT = "RunLeft",
		ANIM_RUN_UP = "RunUp",
		ANIM_RUN_RIGHT = "RunRight",

		//RUN DIAGONAL
		ANIM_RUN_UPLEFT = "RunUpLeft",
		ANIM_RUN_UPRIGHT = "RunUPRight",
		ANIM_RUN_DOWNLEFT = "RunDownLeft",
		ANIM_RUN_DOWNRIGHT = "RunDownRight";
}

Player::Player(Vector2 aSpawnPoint) :
	AnimatedSprite(PLAYER::SPRITESHEET_PATH, 0, 0, PLAYER::WIDTH, PLAYER::HEIGHT, aSpawnPoint, PLAYER::WALK_SPEED * 0.04f)
{
	mDirection = { 0, 0 };
	setupAnimations();
	playAnimation(PLAYER::ANIM_IDLE_RIGHT);
	equipedWeapon = new SolarGun();
}

void Player::load() {
	Texture2D bulletTexture1 = LoadTexture("assets/bullet_1.png");
	bulletTextures.push_back(bulletTexture1);
	equipedWeapon->setBulletTexture(bulletTextures[0]);
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
		playAnimation(PLAYER::ANIM_IDLE_DOWNLEFT);
		break;
	case DOWNRIGHT:
		playAnimation(PLAYER::ANIM_IDLE_DOWNRIGHT);
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

	AnimatedSprite::update(aFrameTime);
	equipedWeapon->update();

	// Controls
	//--------------------------------------------------------------------------------------

	//animations
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
	else if (IsKeyDown(KEY_A) && IsKeyDown(KEY_D) && IsKeyDown(KEY_W))					//LEFT RIGHT UP
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
	Vector2 lSpeed = Vector2{0, 0};
	if (IsKeyDown(KEY_A))
		lSpeed.x += -PLAYER::WALK_SPEED;
	if (IsKeyDown(KEY_D))
		lSpeed.x += PLAYER::WALK_SPEED;
	if (IsKeyDown(KEY_W))
		lSpeed.y += -PLAYER::WALK_SPEED;
	if (IsKeyDown(KEY_S))
		lSpeed.y += PLAYER::WALK_SPEED;

	if (lSpeed.x != 0 && lSpeed.y != 0) {
		lSpeed.x /= std::sqrt(2.0f);
		lSpeed.y /= std::sqrt(2.0f);
	}

	mPosition.x += lSpeed.x;
	mPosition.y += lSpeed.y;

	//boost speed
	if (IsKeyDown(KEY_LEFT_SHIFT)) {
		PLAYER::WALK_SPEED = 8.0f;
	}
	else {
		PLAYER::WALK_SPEED = 2.3f;
	}

	//fire
	if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
		Vector2 lPlayerPosition = getPosition();
		lPlayerPosition.x += PLAYER::WIDTH / 2;
		lPlayerPosition.y += PLAYER::HEIGHT / 2;
		equipedWeapon->fire(lPlayerPosition);
	}

	/* equip solar gun */
	if (IsKeyPressed(KEY_ONE)) {
		equipedWeapon = new SolarGun();
		equipedWeapon->setBulletTexture(bulletTextures[0]);
	}
	/* equip papo gun */
	if (IsKeyPressed(KEY_TWO)) {
		equipedWeapon = new PapoGun();
		equipedWeapon->setBulletTexture(bulletTextures[0]);
	}
	//--------------------------------------------------------------------------------------

}

void Player::draw()
{
	AnimatedSprite::draw();
	equipedWeapon->draw();

}


