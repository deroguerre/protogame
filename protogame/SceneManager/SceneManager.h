#pragma once
#include "Scene.h"

// Class to manage all the scene of the game
class SceneManager 
{
public:
	// Get the instance of SceneManager
	static SceneManager& getInstance();
	// Update the current scene
	void update();
	// Draw the current scene
	void draw();
	// Change the scene, unload and delete the current one then load and set to current the new scene
	void changeScene(Scene* aNewScene);
	//Get the current scene
	Scene* getCurrentScene();

private:
	// Instance of SceneManager
	static SceneManager mInstance;
	// Constructor
	SceneManager();
	// Destructor
	~SceneManager();
	// The current scene
	Scene* mCurrentScene;
};
