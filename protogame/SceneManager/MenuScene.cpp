#include "MenuScene.h"
#include "../Globals.h"

MenuScene::MenuScene() {}

void MenuScene::load() {}

void MenuScene::update() {}

Rectangle playButton = { Globals::SCREEN_WIDTH / 2 - 64, Globals::SCREEN_HEIGHT / 2 - 16, 128, 32 };
Rectangle quitButton = { 32, 96, 128, 32 };

void MenuScene::draw() {

	DrawRectangleRec(playButton, LIGHTGRAY); 
	DrawText("Jouer", playButton.x + playButton.width/2 - (MeasureText("Jouer", 20)/2), playButton.y + playButton.height/2 - 10, 20, BLACK);

	//DrawRectangleRec(quitButton, LIGHTGRAY);
	//DrawText("Quitter", quitButton.x + quitButton.width / 2 - (MeasureText("Quitter", 20) / 2), quitButton.y + quitButton.height / 2 - 10, 20, BLACK);

}

void MenuScene::unload() {}