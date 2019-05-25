#include "bullet.h"

float mBulletSpeed = 8.0f;

Bullet::Bullet(Texture2D aTexture, Vector2 aOrigin, std::string pattern)
{
	mTexture = aTexture;
	mOrigin = aOrigin;

	mPosition = mOrigin;
	mDestination = GetMousePosition();

	lifeTimeCounter = 0;
}


Bullet::~Bullet()
{
	std::cout << "bullet destroy" << std::endl;
}


void Bullet::draw() {

	float angle = atan2(mDestination.y - mOrigin.y, mDestination.x - mOrigin.x);

	float dx = (float)(cos(angle) * mBulletSpeed);
	float dy = (float)(sin(angle) * mBulletSpeed);

	mPosition.x += (float)dx;
	mPosition.y += (float)dy;

	DrawTextureV(mTexture, mPosition, WHITE);

	if (lifeTimeCounter >= 120) {
		isAlive = false;
	}
}