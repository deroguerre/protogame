#include <iostream>
#include <raylib.h>
#include "scGameOver.h"
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
	std::cout << "load Game" << std::endl;

	medievalTileset = LoadTexture("assets/medieval-fantasy/background-elements/0-tileset-x32.png");

	std::vector<std::string> medievalLayers = {
		"maps/1-map_Calque1.csv",
		"maps/1-map_Calque2.csv",
		"maps/1-map_Calque3.csv"
	};
	oRoom = new Room(medievalTileset, medievalLayers, 40, 20);
}


void ScGame::load() {
}

void ScGame::update() {
	//std::cout << "Update Game" << std::endl;

	mCounter--;
	//if (mCounter == 0) {
	//	SceneManager::getInstance().changeScene(new ScGameOver());
	//}

	framesCounter++;

	if (framesCounter >= (60 / framesSpeed))
	{
		framesCounter = 0;
		currentFrame++;

		if (currentFrame > 3) currentFrame = 0;
	}
}

void ScGame::draw() {
	//std::cout << "draw Game" << std::endl;
	int i = 5;
	if (mCounter % 60 == 0) {
		i = mCounter / 60;
	}
	//DrawText(FormatText("%i", mCounter / 60), 300, 100, 500, BLACK);

	oRoom->Draw();

}

void ScGame::unload() {
	//std::cout << "unload Game" << std::endl;
}