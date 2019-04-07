#ifndef PLAYER_H
#define PLAYER_H

#include "animatedsprite.h"
#include "globals.h"

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
	void moveDown();
	void stopMoving();

	void handleTileCollisions(std::vector<Rectangle> aOthersRects);

private:
	Direction mFacing;
	Vector2 mDirection;
};

#endif
