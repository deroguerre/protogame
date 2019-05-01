#pragma once
#include "AnimatedSprite.h"
#include <vector>
#include "Movement.h"

class Enemy : public AnimatedSprite {
public:
	Enemy(const std::string aSpriteSheetPath, const int aWidth, const int aHeight, const float aSpeed, Vector2 aSpawnPoint);
	void handleTileCollisions(std::vector<Rectangle> aOthersRects);

protected:
	Movement* mMovement;
};