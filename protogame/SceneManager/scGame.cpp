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
	mPlayer = Player({ 100, 100 });
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
	oRoom->Draw();
	mPlayer.draw();
}

void ScGame::unload() {}
