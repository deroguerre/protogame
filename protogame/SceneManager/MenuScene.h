#include "../Globals.h"
#include "Scene.h"
#include "SceneManager.h"
#include "GameScene.h"
#include <iostream>

class MenuScene : public Scene 
{
public:
	MenuScene();
	void load() override;
	void update() override;
	void draw() override;
	void unload() override;
	//bool isMouseOver(Rectangle aCheckedRectangle);
private:

};

