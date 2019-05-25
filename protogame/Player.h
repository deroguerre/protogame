#pragma once
#include "AnimatedSprite.h"
#include "Globals.h"
#include "Level.h"
#include "Bullet.h"
#include "Weapon.h"
#include "SolarGun.h"
#include "PapoGun.h"

class Player : public AnimatedSprite 
{
public:

	Player(Vector2 aSpawnPoint);
	void setupAnimations();
	void load();
	void update(float aFrameTime);
	void draw();

	void moveLeft();
	void moveRight();
	void moveUp();
	void moveUpLeft();
	void moveUpRight();
	void moveDown();
	void moveDownLeft();
	void moveDownRight();
	void stopMoving();

	void handleTileCollisions(std::vector<Rectangle> aOthersRects);
	void handleDoorCollisions(Level* aLevel);

private:

	std::vector<Texture2D> bulletTextures;

	Weapon* equipedWeapon = NULL;

	Direction mFacing;
	Vector2 mDirection;
};
