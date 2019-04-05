#include <raylib.h>
#include "scGame.h"
#include "sceneManager.h"
#include "../Room.h"
#include <charconv>

Texture2D medievalTileset;
Room* oRoom;
Rectangle frameRec;

int currentFrame = 0;
int framesCounter = 0;
int framesSpeed = 8;

const float CAMERA_SPEED = 1.5f;
Camera2D mCamera;

ScGame::ScGame() : Scene()
{

	//medievalTileset = LoadTexture("assets/0-tileset-x32.png");
	//std::vector<std::string> medievalLayers = {
	//	"maps/1-map_Calque1.csv",
	//	"maps/1-map_Calque2.csv",
	//	"maps/1-map_Calque3.csv"
	//};
	//oRoom = new Room(medievalTileset, medievalLayers, 40, 20);

	medievalTileset = LoadTexture("assets/2-tileset-x32.png");
	std::vector<std::string> medievalLayers = {
		"maps/2-map_Calque1.csv",
		"maps/2-map_Calque2.csv",
		"maps/2-map_Calque3.csv"
	};
	oRoom = new Room(medievalTileset, medievalLayers, 25, 19);
	//oRoom->blockList;

	mPlayer = Player({ 100, 100 });
}

void ScGame::load() {

	mCamera.target = { mPlayer.getPosition().x, mPlayer.getPosition().y };
	mCamera.offset = { 0, 0 };
	mCamera.rotation = 0.0f;
	mCamera.zoom = 1.0f;

}

void ScGame::update() 
{
	if (IsKeyDown(KEY_LEFT))
	{
		mPlayer.moveLeft();
		mCamera.offset.x += CAMERA_SPEED;
	}
	else if (IsKeyDown(KEY_RIGHT))
	{
		mPlayer.moveRight();
		mCamera.offset.x -= CAMERA_SPEED;
	}

	else if (IsKeyDown(KEY_UP))
	{
		mPlayer.moveUp();
		mCamera.offset.y += CAMERA_SPEED;
	}
	else if (IsKeyDown(KEY_DOWN))
	{
		mPlayer.moveDown();
		mCamera.offset.y -= CAMERA_SPEED;
	}
	else
		mPlayer.stopMoving();

	mPlayer.update(GetFrameTime());
}

void ScGame::draw() 
{
	oRoom->Draw();
	mPlayer.draw();
	//BeginMode2D(mCamera);
	//EndMode2D();
}

void ScGame::unload() {}
