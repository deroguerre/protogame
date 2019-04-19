#ifndef PLAYER_H
#define PLAYER_H

#include "AnimatedSprite.h"
#include "Globals.h"
#include "Level.h"

class Player : public AnimatedSprite 
{
public:
	Player();
	Player(Vector2 aSpawnPoint);
	void setupAnimations();
	void draw();
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

private:
	Direction mFacing;
	Vector2 mDirection;
};

#endif
