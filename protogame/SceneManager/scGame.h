#ifndef SCGAME_H
#define SCGAME_H

#include "scene.h"
#include "../player.h"
#include "../Level.h"

class ScGame : public Scene 
{
public:
	ScGame();
	void load() override;
	void update() override;
	void draw() override;
	void unload() override;
private:
	Player* mPlayer;
	Level* mLevel;
};
#endif
