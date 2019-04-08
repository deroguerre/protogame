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
#include "SceneManager/sceneManager.h"
#include "SceneManager/scIntro.h"
#include "SceneManager/scGame.h"
#include "SceneManager/scMenu.h"
#include "scWorld.h"
#include "globals.h"

SceneManager& mSceneManager = SceneManager::getInstance();

int main()
{
	// Initialization
	//--------------------------------------------------------------------------------------
	InitWindow(GLOBALS::SCREEN_WIDTH, GLOBALS::SCREEN_HEIGHT, "raylib [core] example - basic window");

	SetTargetFPS(60);
	//--------------------------------------------------------------------------------------
	
	mSceneManager.changeScene(new ScGame());

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