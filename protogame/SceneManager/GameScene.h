#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"
#include "../Player.h"
#include "../Level.h"

class GameScene : public Scene 
{
public:
	GameScene();
	void load() override;
	void update() override;
	void draw() override;
	void unload() override;
private:
	Player* mPlayer;
	Level* mLevel;
};
#endif
