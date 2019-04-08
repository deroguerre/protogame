#ifndef SCWORLD_H
#define SCWORLD_H
#include "SceneManager/scene.h"

class scWorld :
	public Scene
{
public:
	scWorld();
	~scWorld();

	void load();
	void update();
	void draw();
	void unload();
};

#endif