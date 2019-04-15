#include <raylib.h>
#include "GameScene.h"
#include "SceneManager.h"
#include "../Globals.h"
//#include "../Level.h"


Room* mRoom;

void GameScene::load() {

}

GameScene::GameScene() : Scene() {
	//mLevel = new Level(8, "room_tilemap");

	Texture2D lTileset = LoadTexture("assets/2-tileset-x32.png");

	std::vector<std::string> lLayers = {
		"maps/2-map_Calque1.csv",
		"maps/2-map_Calque2.csv",
		"maps/2-map_Calque3.csv"
	};

	mRoom = new Room(lTileset, lLayers);
	mRoom->setCollisionTiles({ 0,1,2,3,4,5,10,15,20,25,30,35,40,41,42,43,44,45 });

	mPlayer = new Player(Vector2{ Globals::SCREEN_WIDTH / 2, Globals::SCREEN_HEIGHT / 2 });
}

void GameScene::update() {

	//mLevel->update();
	mPlayer->update(GetFrameTime());

	//mPlayer->handleTileCollisions(mLevel->getCurrentRoom()->getCollisionTiles());
	//mPlayer->handleDoorCollisions(mLevel);
}

void GameScene::draw() {
	//mLevel->draw();
	mRoom->draw();
	mPlayer->draw();
}

void GameScene::unload() {

}
