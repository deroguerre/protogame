#include "SceneManager.h"
#include "Scene.h"

SceneManager SceneManager::mInstance = SceneManager();

SceneManager& SceneManager::getInstance()
{
	return mInstance;
}

void SceneManager::update()
{ 
	mCurrentScene->update(); 
}

void SceneManager::draw() { 
	mCurrentScene->draw();
}

void SceneManager::changeScene(Scene* aNewScene)
{
	if (mCurrentScene != 0)
	{
		mCurrentScene->unload();
		delete mCurrentScene;
	}
	
	mCurrentScene = aNewScene;
	mCurrentScene->load();
}

Scene * SceneManager::getCurrentScene()
{
	return mCurrentScene;
}

// Constructor
SceneManager::SceneManager()
{
}

// Destructor
SceneManager::~SceneManager()
{
}
