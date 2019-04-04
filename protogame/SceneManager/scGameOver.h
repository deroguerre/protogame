#ifndef SCGAMEOVER_H
#define SCGAMEOVER_H

#include "scene.h"

class ScGameOver : public Scene 
{
public:
	ScGameOver();
	void load() override;
	void update() override;
	void draw() override;
	void unload() override;
};
#endif
