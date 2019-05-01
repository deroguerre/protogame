#pragma once
#include "Scene.h"

class IntroScene : public Scene 
{
public:
	IntroScene();
	void load() override;
	void update() override;
	void draw() override;
	void unload() override;
};
