#include <raylib.h>
#include "scGame.h"
#include "sceneManager.h"
#include "../globals.h"
#include "../Room.h"
#include <charconv>
#include "../Level.h"

void ScGame::load() {

}

ScGame::ScGame() : Scene() {
	
	//medievalTileset = LoadTexture("assets/0-tileset-x32.png");
	//std::vector<std::string> medievalLayers = {
	//	"maps/1-map_Calque1.csv",
	//	"maps/1-map_Calque2.csv",
	//	"maps/1-map_Calque3.csv"
	//};
	//oRoom = new Room(medievalTileset, medievalLayers, 40, 20);

	Texture2D lTileset = LoadTexture("assets/2-tileset-x32.png");

	std::vector<std::string> lLayers = {
		"maps/2-map_Calque1.csv",
		"maps/2-map_Calque2.csv",
		"maps/2-map_Calque3.csv"
	};

	mLevel = new Level(8, lTileset, lLayers, { 0,1,2,3,4,5,10,15,20,25,30,35,40,41,42,43,44,45 }, { 37, 47, 48 });
	mPlayer = new Player(Vector2{ GLOBALS::SCREEN_WIDTH / 2, GLOBALS::SCREEN_HEIGHT / 2 });
}

void ScGame::update() {
	mLevel->update();
	mPlayer->update(GetFrameTime());
	mPlayer->handleTileCollisions(mLevel->getCurrentRoom()->getCollisionTiles());
	mPlayer->handleDoorCollisions(mLevel);
}

void ScGame::draw() {
	mLevel->draw();
	mPlayer->draw();
}

void ScGame::unload() {

}
