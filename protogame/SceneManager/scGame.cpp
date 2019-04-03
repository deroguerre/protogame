#include <iostream>
#include <raylib.h>
#include "scGameOver.h"
#include "scGame.h"
#include "sceneManager.h"
#include "../Room.h"
#include "../Player.h"
#include <charconv>

Texture2D dungeonTileset, medivalTileset;
Room* oRoom;
Player* oPlayer;
Rectangle frameRec;

int currentFrame = 0;
int framesCounter = 0;
int framesSpeed = 8;

ScGame::ScGame() : Scene()
{
	std::cout << "load Game" << std::endl;

	dungeonTileset = LoadTexture("assets/dungeon_tileset1.png");
	medivalTileset = LoadTexture("assets/medieval-fantasy/background-elements/0-tileset-x32.png");

	oRoom = new Room(medivalTileset);

	oPlayer = new Player();
	oPlayer->texture = LoadTexture("assets/sprite0.png");

	frameRec = { 0.0f, 0.0f, (float)oPlayer->texture.width / 4, (float)oPlayer->texture.height };
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

		frameRec.x = (float)currentFrame*(float)oPlayer->texture.width / 4;
	}
}

void ScGame::draw() {
	//std::cout << "draw Game" << std::endl;
	int i = 5;
	if (mCounter % 60 == 0) {
		i = mCounter / 60;
	}
	//DrawText(FormatText("%i", mCounter / 60), 300, 100, 500, BLACK);

	//DrawTexture(dungeonTileset, 0, 0, WHITE);
	oRoom->Draw();

	DrawTextureRec(oPlayer->texture, frameRec, oPlayer->position, WHITE);
}

void ScGame::unload() {
	//std::cout << "unload Game" << std::endl;
}