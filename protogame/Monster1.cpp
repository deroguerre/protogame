#include "Monster1.h"

void Monster1::setupAnimations()
{
	//IDLE UP-DOWN-LEFT-RIGHT
	addAnimation(1, true, 0, 0, Monster1Helper::ANIM_IDLE_RIGHT, Monster1Helper::WIDTH, Monster1Helper::HEIGHT);
	addAnimation(1, true, 0, Monster1Helper::HEIGHT, Monster1Helper::ANIM_IDLE_LEFT, Monster1Helper::WIDTH, Monster1Helper::HEIGHT);

	//WALK UP-DOWN-LEFT-RIGHT
	addAnimation(4, true, 0, 0, Monster1Helper::ANIM_RUN_RIGHT, Monster1Helper::WIDTH, Monster1Helper::HEIGHT);
	addAnimation(4, true, 0, Monster1Helper::HEIGHT, Monster1Helper::ANIM_RUN_LEFT, Monster1Helper::WIDTH, Monster1Helper::HEIGHT);
}

Monster1::Monster1(Vector2 aSpawnPoint, Player* aPlayer) : Enemy(Monster1Helper::SPRITESHEET_PATH, Monster1Helper::WIDTH, Monster1Helper::HEIGHT, Monster1Helper::ANIMATION_SPEED, aSpawnPoint)
{
	setupAnimations();
	playAnimation(Monster1Helper::ANIM_IDLE_RIGHT);
	mMovement = new FollowPlayerMovement(aSpawnPoint, Monster1Helper::WALK_SPEED, aPlayer);
}

void Monster1::update(float aFrameTime)
{
	AnimatedSprite::update(aFrameTime);
	playAnimation(Monster1Helper::ANIM_RUN_RIGHT);
	mMovement->update(aFrameTime);
	mPosition = mMovement->getPosition();
}




