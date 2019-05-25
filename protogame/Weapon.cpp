#include "Weapon.h"

Weapon::Weapon() {
	cout << "weapon created" << endl;
}

Weapon::~Weapon() {
	cout << "weapon destroyed" << endl;
}

void Weapon::update() {
	elapsedTime++;
}

void Weapon::fire(Vector2 aOrigin) {
}

void Weapon::draw() {

	/* draw all fired bullets and check life cycle */
	for (int i = 0; i < firedBullets.size(); i++) {

		firedBullets[i]->lifeTimeCounter++;

		if (firedBullets[i]->isAlive) {
			firedBullets[i]->draw();
		}
		else {
			delete firedBullets[i];
			firedBullets.erase(firedBullets.begin() + i);
		}
	}
}
