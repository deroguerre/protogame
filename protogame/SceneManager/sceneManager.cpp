#include "sceneManager.h"
#include "scene.h"

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
	if (mInstance.mCurrentScene != 0)
	{
		mInstance.mCurrentScene->unload();
	}
	delete mInstance.mCurrentScene;
	mInstance.mCurrentScene = aNewScene;
	mInstance.mCurrentScene->load();
}

Scene * SceneManager::getCurrentScene()
{
	return mInstance.mCurrentScene;
}

// Constructor
SceneManager::SceneManager()
{
}

// Destructor
SceneManager::~SceneManager()
{
}
