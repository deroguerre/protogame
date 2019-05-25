#pragma once
#include "Globals.h"
#include "Bullet.h"
#include <vector>
#include <iostream>

class Weapon
{
public:
	std::vector<Bullet*> firedBullets;

	Weapon();
	~Weapon();
	virtual void update();
	void draw();

	void setBulletTexture(Texture2D texture) { bulletTexture = texture; };
	virtual void fire(Vector2 origin);

	float elapsedTime;
protected:
	Texture2D bulletTexture;

private:
};

