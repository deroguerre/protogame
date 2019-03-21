#include "scMenu.h"
#include <iostream>
#include "sceneManager.h";
#include "scGame.h"

ScMenu::ScMenu()
{
}

void ScMenu::load() {
	std::cout << "load Menu" << std::endl;
}

void ScMenu::update() {
	std::cout << "Update Menu" << std::endl;
	if (IsKeyDown(KEY_B)) {
		SceneManager::getInstance().changeScene(new ScIntro);
	}
	else if (IsKeyPressed(KEY_ENTER)) {
		SceneManager::getInstance().changeScene(new ScGame);
	}
}

void ScMenu::draw() {
	DrawText("MENU", 350, 150, 40, BLACK);
	DrawText("Press Enter to play", 330, 500, 15, BLACK);
	std::cout << "draw Menu" << std::endl;
}

void ScMenu::unload() {
	std::cout << "unload Menu" << std::endl;
}