#pragma once
#include "SceneManager/scene.h"
class ScWorldmap :
	public Scene
{
public:
	ScWorldmap();
	~ScWorldmap();

	void load() override;
	void update() override;
	void draw() override;
	void unload() override;
};

