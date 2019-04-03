#ifndef SCMENU_H
#define SCMENU_H

#include "scene.h"

class ScMenu : public Scene 
{
public:
	ScMenu();
	void load() override;
	void update() override;
	void draw() override;
	void unload() override;
};

#endif
