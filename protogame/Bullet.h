#pragma once
#include <raylib.h>
#include <cmath>
#include <iostream>

class Bullet
{
public:
	bool isAlive = true;
	int mLifeTimeCounter;
	Vector2 mOrigin;
	Texture2D mTexture;

	Bullet(Texture2D aBulletTexture, Vector2 aOrigin);
	~Bullet();

	void draw();
private:
	Vector2 mDestination;
	Vector2 mPosition;
};

