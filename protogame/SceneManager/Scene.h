#pragma once
#include <raylib.h>

class Scene 
{
public:
	virtual void load() {}
	virtual void update() {}
	virtual void draw() {}
	virtual void unload() {}
};

