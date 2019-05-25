#pragma once
#include "Weapon.h"

class SolarGun :
	public Weapon
{
public:
	SolarGun();
	~SolarGun();
	void fire(Vector2 origin);
	void draw();
private:
	float _fireRate = 10.0f;
};

