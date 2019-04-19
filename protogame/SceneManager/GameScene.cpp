#include <raylib.h>
#include "GameScene.h"
#include "SceneManager.h"
#include "../Globals.h"
#include "../TilemapXmlParser.h"
#include "../World.h"
//#include "../Level.h"

Camera2D mCamera;
Room* mRoom;
World* mWorld;

void GameScene::load() {

}

GameScene::GameScene() : Scene() {
	//mLevel = new Level(8, "room_tilemap");

	Texture2D lTileset = LoadTexture("assets/0-tileset-x32.png");
	std::string aTilemap = "maps/world_tilemap.tmx";

	//mRoom = new Room(aTilemap, lTileset);
	//mRoom->setCollisionTiles({ 1,2,3,4,5,6,11,16,21,26,31,36,41,42,43,44,45,46});

	mPlayer = new Player(Vector2{ Globals::SCREEN_WIDTH / 2, Globals::SCREEN_HEIGHT / 2 });
	mCamera.offset = { 0, 0 };
	mCamera.target = { mPlayer->getPosition().x, mPlayer->getPosition().y };
	mCamera.rotation = 0.0f;
	mCamera.zoom = 1.0f;

	mWorld = new World();

	//double lTime = GetTime();
	//TilemapXmlParser* lParser = new TilemapXmlParser("world_tilemap");
	//double lElapsedTime = GetTime() - lTime;
	//std::cout << "\nElapsed time: " << lElapsedTime;
 //	std::cout << "\nTilemap size: (" << lParser->getTilemapSize().x << ", " << lParser->getTilemapSize().y << ")";

}

void GameScene::update() {

	//mLevel->update();
	
	mPlayer->update(GetFrameTime());
	
	

	int x = (int)abs(mCamera.offset.x) % 32;
	int y = (int)abs(mCamera.offset.y) % 32;
	if (IsKeyDown(KEY_W) || IsKeyDown(KEY_A) || IsKeyDown(KEY_S) || IsKeyDown(KEY_D)) {
		mCamera.offset.x = -(mPlayer->getPosition().x - Globals::SCREEN_WIDTH / 2);
		mCamera.offset.y = -(mPlayer->getPosition().y - Globals::SCREEN_HEIGHT / 2);
		std::cout << "\nCamera offset: (" << abs(mCamera.offset.x) << ", " << abs(mCamera.offset.y) << ")";
	}
	mWorld->update(Vector2{ mCamera.offset.x / 32, mCamera.offset.y / 32 });

	//mPlayer->handleTileCollisions(mLevel->getCurrentRoom()->getCollisionTiles());
	//mPlayer->handleDoorCollisions(mLevel);
}

void GameScene::draw() {
	//mLevel->draw();
	BeginMode2D(mCamera);
		mWorld->draw();
		//mRoom->draw();
		mPlayer->draw();
	EndMode2D();
}

void GameScene::unload() {

}
