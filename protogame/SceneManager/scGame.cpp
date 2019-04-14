#include <raylib.h>
#include "scGame.h"
#include "sceneManager.h"
#include "../globals.h"
#include "../world.h"
#include <charconv>
#include "../Level.h"
#include "../Room.h"


Room* mRoom;

void ScGame::load() {

}

ScGame::ScGame() : Scene() {
	mLevel = new Level(8, "room_tilemap");
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
