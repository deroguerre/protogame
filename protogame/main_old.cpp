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

#include <string>
#include <iostream>
#include <raylib.h>
#include "SceneEngine.h"

using namespace std;

#define MAX_FRAME_SPEED 15
#define MIN_FRAME_SPEED 1

int main()
{
	// Initialization
	//--------------------------------------------------------------------------------------
	int screenWidth = 800;
	int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

	Texture2D kingy = LoadTexture("assets/sprite0.png");
	Texture2D kingyLeft = kingy;
	kingyLeft.width *= -1;

	Vector2 kingyPosition = { (float)kingy.width / 2, (float)kingy.height / 2 };

	Vector2 position = { 350.0f, 280.0f };
	Rectangle frameRec = { 0.0f, 0.0f, (float)kingy.width / 4, (float)kingy.height };
	Rectangle idleFrameRec = { 0.0f, 0.0f, (float)kingy.width / 4, (float)kingy.height };

	int currentFrame = 0;

	int framesCounter = 0;
	int framesSpeed = 8;

	SceneEngine sceneEngine;

	sceneEngine.console("Salut c'est moi mr larbin");

	SetTargetFPS(60);
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		framesCounter++;
		if (framesCounter >= (60 / framesSpeed)) {
			framesCounter = 0;
			currentFrame++;

			if (currentFrame > 3) {
				currentFrame = 0;
			}

			frameRec.x = (float)currentFrame*(float)kingy.width / 4;
		}

		if (IsKeyDown(KEY_RIGHT)) {
			position.x += 2.0f;
			//framesSpeed++;
		}
		else if(IsKeyDown(KEY_LEFT)){
			position.x -= 2.0f;
			//framesSpeed--;
		}

		if (framesSpeed > MAX_FRAME_SPEED) {
			framesSpeed = MAX_FRAME_SPEED;
		}
		else if (framesSpeed < MIN_FRAME_SPEED) {
			framesSpeed = MIN_FRAME_SPEED;
		}
		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

			ClearBackground(RAYWHITE);

			//DrawTexture(kingy, 15, 40, WHITE);
			//DrawRectangleLines(15, 40, kingy.width, kingy.height, LIME);
			//DrawRectangleLines(15 + frameRec.x, 40 + frameRec.y, frameRec.width, frameRec.height, RED);

			//for (int i = 0; i > MAX_FRAME_SPEED; i++) {
			//	if (i < framesSpeed) {
			//		DrawRectangle(250 + 21 * i, 205, 20, 20, RED);
			//	}
			//	DrawRectangleLines(250 + 21 * i, 205, 20, 20, MAROON);
			//}

			if (IsKeyDown(KEY_RIGHT)) {

				DrawTextureRec(kingy, frameRec, position, WHITE);
			}
			else if (IsKeyDown(KEY_LEFT)) {

				DrawTextureRec(kingyLeft, frameRec, position, WHITE);
			}
			else {
				DrawTextureRec(kingy, idleFrameRec, position, WHITE);
			}

			//DrawText("Congrats! You created your first window!", 190, 200, 20, MAROON);

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------   
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}

//Rectangle RectangleScale(Rectangle rec, float xScale, float yScale) {
//
//	return (Rectangle) { rec.x, rec.y, rec.width*xScale, rec.height*yScale };
//}