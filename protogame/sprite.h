#ifndef SPRITE_H
#define SPRITE_H

#include <raylib.h>
#include <string>

class Sprite 
{
public:
	Sprite();
	Sprite(const std::string &aFilePath, int aSourceX, int aSourceY, int aWidth, int aHeight, Vector2 aPosition);
	virtual void update(float aFrameTime) = 0;
	void draw(Vector2 aPosition);
	Vector2 getPosition();

protected:
	Rectangle mSourceRect;
	Texture2D mSpriteSheet;
	Vector2 mPosition;
};

#endif
