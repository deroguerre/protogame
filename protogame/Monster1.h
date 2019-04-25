#ifndef MONSTER1_H
#define MONSTER1_H

#include "Enemy.h"
#include "Player.h"

namespace Monster1Helper {
	const std::string SPRITESHEET_PATH = "assets/enemy/monster_1.png";
	const int WIDTH = 32;
	const int HEIGHT = 32;
	const float WALK_SPEED = 2.0f;
	const float ANIMATION_SPEED = 0.1f;

	//IDLE UP-DOWN-LEFT-RIGHT
	const std::string ANIM_IDLE_LEFT = "IdleLeft";
	const std::string ANIM_IDLE_RIGHT = "IdleRight";

	//RUN UP-DOWN-LEFT-RIGHT
	const std::string ANIM_RUN_LEFT = "RunLeft";
	const std::string ANIM_RUN_RIGHT = "RunRight";
}

class Monster1 : public Enemy {
public:
	Monster1(Vector2 aSpawnPoint, Player* aPlayer);
	void update(float aFrameTime);
	void setupAnimations();
private:

};

#endif