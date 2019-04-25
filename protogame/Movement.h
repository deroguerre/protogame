#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <raylib.h>
#include <math.h>
#include <algorithm>
#include "Player.h"

class Movement {
public:
	virtual void update(float aFrameTime) = 0;
	Vector2 getPosition() {
		return mPosition;
	}
protected:
	Vector2 mPosition;
};

class CircularMovement : public Movement {
public:
	CircularMovement(Vector2 aOrigin, int aRadius) {
		mOrigin = aOrigin;
		mRadius = aRadius;
	}

	void update(float aFrameTime) {
		mCounter += aFrameTime;
		float lX, lY;
		lX = mOrigin.x + cos(mCounter) * mRadius;
		lY = mOrigin.y + sin(mCounter) * mRadius;

		mPosition.y = lY;
		mPosition.x = lX;
	}
private:
	Vector2 mOrigin;
	int mRadius;
	float mCounter = 0.0f;
};

class FollowPlayerMovement : public Movement {
public:
	FollowPlayerMovement(Vector2 aPosition, const float aSpeed, Player* aPlayer, Vector3 aAreaDetection = {0, 0, 0}) {
		mPosition = aPosition;
		mSpeed = aSpeed;
		mPlayer = aPlayer;
		mAreaDetection = aAreaDetection;
	}

	void update(float aFrameTime) {
		bool lFollow = false;
		if (mAreaDetection.z > 0) {
			float lCircleX = mAreaDetection.x;
			float lCircleY = mAreaDetection.y;
			float lRadius = mAreaDetection.z;

			float lDeltaX = lCircleX - max(mPlayer->getCollisionRect().x, min(lCircleX, mPlayer->getCollisionRect().x + mPlayer->getCollisionRect().width));
			float lDeltaY = lCircleY - max(mPlayer->getCollisionRect().y, min(lCircleY, mPlayer->getCollisionRect().y + mPlayer->getCollisionRect().height));
			
			if ((lDeltaX * lDeltaX + lDeltaY * lDeltaY) < (lRadius * lRadius)) {
				lFollow = true;
			}
		}
		else {
			lFollow = true;
		}

		if (lFollow) {
			mDirection.x = mPlayer->getPosition().x - mPosition.x;
			mDirection.y = mPlayer->getPosition().y - mPosition.y;

			float lHypotenuse = sqrt(mDirection.x * mDirection.x + mDirection.y * mDirection.y);
			mDirection.x /= lHypotenuse;
			mDirection.y /= lHypotenuse;

			mPosition.x += mDirection.x * mSpeed;
			mPosition.y += mDirection.y * mSpeed;

			mAreaDetection.x += mDirection.x * mSpeed;
			mAreaDetection.y += mDirection.y * mSpeed;
		}
	}

private:
	float mSpeed;
	Player* mPlayer;
	Vector2 mDirection;
	Vector3 mAreaDetection;
};
#endif
