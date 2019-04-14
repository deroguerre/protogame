#ifndef WORLDMAPSCENE_H
#define WORLDMAPSCENE_H

#include "SceneManager/Scene.h"
class WorldMapScene :
	public Scene
{
public:
	WorldMapScene();
	~WorldMapScene();

	void load() override;
	void update() override;
	void draw() override;
	void unload() override;
};

#endif

