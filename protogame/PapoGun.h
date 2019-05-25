#pragma once
#include "Weapon.h"

class PapoGun :
	public Weapon
{
public:
	PapoGun();
	~PapoGun();
	void fire(Vector2 aOrigin);
private:
	float _fireRate = 5.0f;
};

