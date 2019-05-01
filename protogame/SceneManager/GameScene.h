#pragma once
#include "../Globals.h"
#include "../TilemapXmlParser.h"
#include "Scene.h"
#include "SceneManager.h"
#include "../Player.h"
#include "../Level.h"
#include "../World.h"

class GameScene : public Scene 
{
public:
	GameScene();
	void load() override;
	void update() override;
	void draw() override;
	void unload() override;
private:
	Player* mPlayer;
	Level* mLevel;
};
