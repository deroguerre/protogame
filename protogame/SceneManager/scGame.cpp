#include <raylib.h>
#include "scGame.h"
#include "../globals.h"

std::vector<Rectangle> mWalls;

ScGame::ScGame() : Scene()
{
	mPlayer = Player(Vector2{ GLOBALS::SCREEN_WIDTH / 2, GLOBALS::SCREEN_HEIGHT / 2 });
}

void ScGame::load() 
{
	mRoom = LoadTexture("assets/room.png");

	mWalls.push_back({ 0.0f, 0.0f, (float)mRoom.width, 32.0f });
	mWalls.push_back({ 0.0f, (float)mRoom.height - 32.0f, (float)mRoom.width, 32.0f });
	mWalls.push_back({ 0.0f, 0.0f, 32.0f, (float)mRoom.height });
	mWalls.push_back({ (float)mRoom.width - 32.0f, 0.0f, 32.0f, (float)mRoom.height });
}

void ScGame::update() 
{
	if (IsKeyPressed(KEY_F11))
		ToggleFullscreen();


	if (IsKeyDown(KEY_LEFT)) {
		mPlayer.moveLeft();
	}
	else if (IsKeyDown(KEY_RIGHT)) {
		mPlayer.moveRight();
	}
	else if (IsKeyDown(KEY_UP))	{
		mPlayer.moveUp();
	}
	else if (IsKeyDown(KEY_DOWN)) {
		mPlayer.moveDown();
	}
	else {
		mPlayer.stopMoving();
	}

	mPlayer.update(GetFrameTime());

	std::vector<Rectangle> lCollisions;
	for (auto lWall : mWalls)
		if (CheckCollisionRecs(mPlayer.getCollisionRect(), lWall))
			lCollisions.push_back(lWall);

	if (lCollisions.size() > 0)
		mPlayer.handleTileCollisions(lCollisions);
}

void ScGame::draw() 
{
	DrawTexture(mRoom, 0, 0, RAYWHITE);
	mPlayer.draw();
}

void ScGame::unload() {
	UnloadTexture(mRoom);
}