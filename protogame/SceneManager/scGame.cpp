#include <raylib.h>
#include "scGame.h"

ScGame::ScGame() : Scene()
{
	mPlayer = Player(Vector2{ 20, 20 });
}

void ScGame::load() {}

void ScGame::update() 
{
	if (IsKeyDown(KEY_LEFT))
		mPlayer.moveLeft();
	else if (IsKeyDown(KEY_RIGHT))
		mPlayer.moveRight();
	else if (IsKeyDown(KEY_UP)) 
		mPlayer.moveUp();
	else if (IsKeyDown(KEY_DOWN))
		mPlayer.moveDown();
	else
		mPlayer.stopMoving();

	mPlayer.update(GetFrameTime());
}

void ScGame::draw() 
{
	mPlayer.draw();
}

void ScGame::unload() {}