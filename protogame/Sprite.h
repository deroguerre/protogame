#pragma once
#include <raylib.h>
#include <string>
#include "Globals.h"

class Sprite 
{
public:
	Sprite();
	Sprite(const std::string &aFilePath, int aSourceX, int aSourceY, int aWidth, int aHeight, Vector2 aPosition);
	virtual void update(float aFrameTime) = 0;
	void draw();
	Vector2 getPosition();
	void setPosition(Vector2 aPosition);
	const Rectangle getCollisionRect() const { return mCollisionRect; }
	const Sides::Side getCollisionSide(Rectangle aOtherRect) const;

protected:
	Rectangle mSourceRect;
	Rectangle mCollisionRect;
	Texture2D mSpriteSheet;
	Vector2 mPosition;
};
