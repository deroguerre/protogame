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
	std::string aTilemap = "maps/2-map.tmx";

	mRoom = new Room(aTilemap, lTileset);
	mRoom->setCollisionTiles({ 1,2,3,4,5,6,11,16,21,26,31,36,41,42,43,44,45,46});

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
