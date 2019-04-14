#ifndef GAMEOVERSCENE_H
#define GAMEOVERSCENE_H

#include "Scene.h"

class GameOverScene : public Scene 
{
public:
	GameOverScene();
	void load() override;
	void update() override;
	void draw() override;
	void unload() override;
};
#endif
