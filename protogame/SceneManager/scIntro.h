#pragma once

#ifndef SCINTRO_H
#define SCINTRO_H
#include "scene.h"

class ScIntro : public Scene {
public:
	ScIntro();
	void load() override;
	void update() override;
	void draw() override;
	void unload() override;
};

#endif
