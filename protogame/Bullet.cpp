#include "bullet.h"

float mBulletSpeed = 8.0f;

Bullet::Bullet(Texture2D aTexture, Vector2 aOrigin)
{
	mTexture = aTexture;
	mOrigin = aOrigin;

	mPosition = mOrigin;
	mDestination = GetMousePosition();

	mLifeTimeCounter = 0;
}


Bullet::~Bullet()
{
	std::cout << "bullet destroy" << std::endl;
}


void Bullet::draw() {

	float angle = atan2(mDestination.y - mOrigin.y, mDestination.x - mOrigin.x);

	double dx = (double)(cos(angle) * mBulletSpeed);
	double dy = (double)(sin(angle) * mBulletSpeed);

	mPosition.x += dx;
	mPosition.y += dy;

	DrawTextureV(mTexture, mPosition, WHITE);

	if (mLifeTimeCounter >= 120) {
		isAlive = false;
	}
}