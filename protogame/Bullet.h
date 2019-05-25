#pragma once
#include <raylib.h>
#include <cmath>
#include <iostream>

class Bullet
{
public:
	bool isAlive = true;
	int lifeTimeCounter;
	Vector2 mOrigin;
	Texture2D mTexture;

	Bullet(Texture2D aBulletTexture, Vector2 aOrigin, std::string pattern);
	~Bullet();

	void draw();
private:
	Vector2 mPosition;
	Vector2 mDestination;
};

