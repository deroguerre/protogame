#include <raylib.h>
#include "Globals.h"
#include "SceneManager/SceneManager.h"
//#include "SceneManager/IntroScene.h"
#include "SceneManager/MenuScene.h"
#include "SceneManager/GameScene.h"
//#include "WorldMapScene.h"

SceneManager& mSceneManager = SceneManager::getInstance();

int main()
{
	// Initialization
	//--------------------------------------------------------------------------------------
	SetConfigFlags(FLAG_VSYNC_HINT);
	InitWindow(Globals::SCREEN_WIDTH, Globals::SCREEN_HEIGHT, "raylib [core] example - basic window");

	SetTargetFPS(60);
	//--------------------------------------------------------------------------------------
	
	mSceneManager.changeScene(new GameScene());

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		if (IsKeyPressed(KEY_F11) || IsKeyPressed(KEY_F))
			ToggleFullscreen();

		mSceneManager.update();
		//----------------------------------------------------------------------------------


		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

			ClearBackground(RAYWHITE);
			mSceneManager.draw();

			if (Globals::DEBUG) {
				DrawFPS(0, 0);
			}

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	mSceneManager.getCurrentScene()->unload();

	// De-Initialization
	//--------------------------------------------------------------------------------------   
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}