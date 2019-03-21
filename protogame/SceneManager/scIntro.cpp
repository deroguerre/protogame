#include <iostream>
#include <raylib.h>
#include "scIntro.h"
#include "scMenu.h"
#include "sceneManager.h"


ScIntro::ScIntro() : Scene()
{
}

void ScIntro::load() {
	std::cout << "load Intro" << std::endl;
}

void ScIntro::update() {
	std::cout << "Update Intro" << std::endl;
	if (IsKeyPressed(KEY_ENTER)) {
		SceneManager::getInstance().changeScene(new ScMenu);
	}
}

void ScIntro::draw() {
	std::cout << "draw Intro" << std::endl;
	DrawText("PROTOGAME", 260, 150, 40, BLACK);
	DrawText("Press Enter to start", 330, 500, 15, BLACK);
}

void ScIntro::unload() {
	std::cout << "unload Intro" << std::endl;
}