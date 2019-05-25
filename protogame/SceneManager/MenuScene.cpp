#include "MenuScene.h"

Color playBtnColor = LIGHTGRAY;
Rectangle playButton = { Globals::SCREEN_WIDTH / 2 - 64, Globals::SCREEN_HEIGHT / 2 - 16, 128, 32 };
Rectangle quitButton = { 32, 96, 128, 32 };

MenuScene::MenuScene() {}

void MenuScene::load() {

}

void MenuScene::update() {

	//MOUSE EVENTS
	//-----------------------------------------------------------------------
	if (isMouseOver(playButton)) {
		playBtnColor = SKYBLUE;

		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			SceneManager::getInstance().changeScene(new GameScene());
			std::cout << "top" << std::endl;
		}
	}
	else {
		playBtnColor = LIGHTGRAY;
	}
	//-----------------------------------------------------------------------
}

void MenuScene::draw() {


	DrawRectangleRec(playButton, playBtnColor);
	DrawText("Jouer", (int)playButton.x + (int)playButton.width/2 - (MeasureText("Jouer", 20)/2), (int)playButton.y + (int)playButton.height/2 - 10, 20, BLACK);

	//DrawRectangleRec(quitButton, LIGHTGRAY);
	//DrawText("Quitter", quitButton.x + quitButton.width / 2 - (MeasureText("Quitter", 20) / 2), quitButton.y + quitButton.height / 2 - 10, 20, BLACK);
}

void MenuScene::unload() {}