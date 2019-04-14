#include "scworldmap.h"
#include "SceneManager/sceneManager.h"
#include "globals.h"
#include "world.h"
#include <charconv>
#include "Level.h"
#include "player.h"

World* objWorld;
Player* mPlayer;

ScWorldmap::ScWorldmap()
{
	Texture2D lTileset = LoadTexture("assets/overworld_tileset_grass.png");

	std::vector<std::string> lLayers = {
		"maps/world-map_Calque1.csv",
		"maps/world-map_Calque2.csv",
		"maps/world-map_Calque3.csv"
	};

	std::pair<int, int> aPosition = { 0,0 };

	objWorld = new World(aPosition, lTileset, lLayers, 16);

	mPlayer = new Player(Vector2{ GLOBALS::SCREEN_WIDTH / 2, GLOBALS::SCREEN_HEIGHT / 2 });
}


ScWorldmap::~ScWorldmap() {
}

void ScWorldmap::load() {
}

void ScWorldmap::update() {
	mPlayer->update(GetFrameTime());
}

void ScWorldmap::draw() {
	objWorld->draw();
	mPlayer->draw();
}

void ScWorldmap::unload() {
}
