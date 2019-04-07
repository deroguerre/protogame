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
	oRoom->BlockListCreator({ 0,1,2,3,4,5,10,15,20,25,30,35,40,41,42,43,44,45 });

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
	mPlayer.update(GetFrameTime());
}

void ScGame::draw()
{
	oRoom->Draw();
	mPlayer.draw();
}

void ScGame::unload() {}
