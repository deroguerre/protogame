#include "Enemy.h"
#include <math.h>

Enemy::Enemy(const std::string aSpriteSheetPath, const int aWidth, const int aHeight, const float aAnimationSpeed, Vector2 aSpawnPoint) :
	AnimatedSprite(aSpriteSheetPath, 0, 0, aWidth, aHeight, aSpawnPoint, aAnimationSpeed)
{
}

void Enemy::handleTileCollisions(std::vector<Rectangle> aOthersRects)
{
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
				case Sides::TOP: //Enemy Top side
					mPosition.y = lCollision.y + lCollision.height + 1;
					break;
				case Sides::BOTTOM: //Enemy Bottom side
					mPosition.y = lCollision.y - Sprite::getCollisionRect().height - 1;
					break;
				case Sides::LEFT: //Enemy Left side
					mPosition.x = lCollision.x + lCollision.width + 1;
					break;
				case Sides::RIGHT: //Enemy Right side
					mPosition.x = lCollision.x - Sprite::getCollisionRect().width - 1;
					break;
				}
			}
		}
	}
}
