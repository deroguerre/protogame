#pragma once
#ifndef SCGAME_H
#define SCGAME_H
#include "scene.h"

class ScGame : public Scene {
public:
	ScGame();
	void load() override;
	void update() override;
	void draw() override;
	void unload() override;
private:
	int mCounter = 6 * 60;
};
#endif#pragma once
