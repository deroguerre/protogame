#include "PapoGun.h"

PapoGun::PapoGun() {
}

PapoGun::~PapoGun() {
}

void PapoGun::fire(Vector2 origin) {


	if (elapsedTime >= (60 / _fireRate)) {

		for (size_t i = 0; i < 10; i++)
		{
			Bullet* lBullet = new Bullet(bulletTexture, origin, "linear");
			firedBullets.push_back(lBullet);
		}

		elapsedTime = 0;

		cout << "papo shot" << endl;
		if (Globals::DEBUG) {
			//std::cout << _firedBullets.size() << std::endl;
		}
	}
}
