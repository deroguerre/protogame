#ifndef SCGAME_H
#define SCGAME_H

#include "scene.h"
#include "../player.h"

class ScGame : public Scene 
{
public:
	ScGame();
	void load() override;
	void update() override;
	void draw() override;
	void unload() override;
private:
	Player mPlayer;
	Texture2D mRoom;
	Camera2D mCamera;
};
#endif
