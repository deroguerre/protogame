#include <iostream>
#include <raylib.h>
#include "scGameOver.h"
#include "scIntro.h"
#include "sceneManager.h"

ScGameOver::ScGameOver() : Scene()
{
}

void ScGameOver::load() {
	std::cout << "load Game Over" << std::endl;
}

void ScGameOver::update() {
	std::cout << "Update Game Over" << std::endl;
	if (IsKeyPressed(KEY_ENTER)) {
		SceneManager::getInstance().changeScene(new ScIntro);
	}
}

void ScGameOver::draw() {
	std::cout << "draw Game Over" << std::endl;
	DrawText("GAME OVER", 260, 150, 40, BLACK);
	DrawText("Press Enter", 350, 500, 15, BLACK);
}

void ScGameOver::unload() {
	std::cout << "unload Game Over" << std::endl;
}