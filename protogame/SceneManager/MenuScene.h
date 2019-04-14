#ifndef MENUSCENE_H
#define MENUSCENE_H

#include "Scene.h"

class MenuScene : public Scene 
{
public:
	MenuScene();
	void load() override;
	void update() override;
	void draw() override;
	void unload() override;
};

#endif
