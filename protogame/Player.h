#pragma once
#include "AnimatedSprite.h"
#include "Globals.h"
#include "Level.h"
#include "Bullet.h"

class Player : public AnimatedSprite 
{
public:
	float mFrameCounter = 0;

	Player(Vector2 aSpawnPoint);
	void setupAnimations();
	void draw();
	void load();
	void update(float aFrameTime);

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

	void fire();


private:
	float mFireRate = 10.0f;

	Direction mFacing;
	Vector2 mDirection;

	Texture2D mBulletTexture;
	std::vector<Bullet*> mFiredBullets;
};
