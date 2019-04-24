/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2016 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include <raylib.h>
#include "SceneManager/SceneManager.h"
#include "SceneManager/IntroScene.h"
#include "SceneManager/GameScene.h"
#include "SceneManager/MenuScene.h"
//#include "WorldMapScene.h"
#include "Globals.h"

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
				DrawFPS(0.0f, 0.0f);
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