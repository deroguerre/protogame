#include "SolarGun.h"

SolarGun::SolarGun() {
}

SolarGun::~SolarGun() {
}

void SolarGun::fire(Vector2 origin) {

	/* create bullet every fire rate and pushing it to the fired bullets pool */
	if (elapsedTime >= (60 / _fireRate)) {

		Bullet* lBullet = new Bullet(bulletTexture, origin, "linear");
		firedBullets.push_back(lBullet);

		elapsedTime = 0;

		cout << "solar shot" << endl;
		if (Globals::DEBUG) {
			//std::cout << _firedBullets.size() << std::endl;
		}
	}
}

void SolarGun::draw() {

}
