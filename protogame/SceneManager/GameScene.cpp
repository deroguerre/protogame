#include <raylib.h>
#include "GameScene.h"

Camera2D mCamera;
Room* mRoom;
//World* mWorld;

void GameScene::load() {

	mPlayer->load();
}

GameScene::GameScene() : Scene() {

	mLevel = new Level(8, "maps/dungeon_map.tmx");

	mPlayer = new Player(Vector2{ Globals::SCREEN_WIDTH / 2, Globals::SCREEN_HEIGHT / 2 });
	
	
	//mCamera.offset = { 0, 0 };
	//mCamera.target = { mPlayer->getPosition().x, mPlayer->getPosition().y };
	//mCamera.rotation = 0.0f;
	//mCamera.zoom = 1.0f;

	//mWorld = new World();
}

void GameScene::update() {

	mLevel->update();

	mPlayer->update(GetFrameTime());

	/*int x = (int)abs(mCamera.offset.x) % 32;
	int y = (int)abs(mCamera.offset.y) % 32;
	if (IsKeyDown(KEY_W) || IsKeyDown(KEY_A) || IsKeyDown(KEY_S) || IsKeyDown(KEY_D)) {
		mCamera.offset.x = -(mPlayer->getPosition().x - Globals::SCREEN_WIDTH / 2);
		mCamera.offset.y = -(mPlayer->getPosition().y - Globals::SCREEN_HEIGHT / 2);
		std::cout << "\nCamera offset: (" << abs(mCamera.offset.x) << ", " << abs(mCamera.offset.y) << ")";
	}*/
	//mWorld->update(Vector2{ mCamera.offset.x / 32, mCamera.offset.y / 32 });

	mPlayer->handleTileCollisions(mLevel->getCurrentRoom()->getCollisionTiles());

	mPlayer->handleDoorCollisions(mLevel);
}

void GameScene::draw() {
	mLevel->draw();
	//BeginMode2D(mCamera);
	//	//mWorld->draw();
	//EndMode2D();
	mPlayer->draw();
}

void GameScene::unload() {

}
