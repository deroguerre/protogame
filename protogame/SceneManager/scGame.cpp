#include <iostream>
#include <raylib.h>
#include "scGameOver.h"
#include "scGame.h"
#include "sceneManager.h"
#include <charconv>

ScGame::ScGame() : Scene()
{
}

void ScGame::load() {
	std::cout << "load Game" << std::endl;
}

void ScGame::update() {
	std::cout << "Update Game" << std::endl;

	mCounter--;
	if (mCounter == 0) {
		SceneManager::getInstance().changeScene(new ScGameOver());
	}
}

void ScGame::draw() {
	std::cout << "draw Game" << std::endl;
	int i = 5;
	if (mCounter % 60 == 0) {
		i = mCounter / 60;
	}
	DrawText(FormatText("%i", mCounter / 60), 300, 100, 500, BLACK);
}

void ScGame::unload() {
	std::cout << "unload Game" << std::endl;
}