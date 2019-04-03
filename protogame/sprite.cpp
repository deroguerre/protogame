#include "sprite.h"

Sprite::Sprite() {}

Sprite::Sprite(const std::string &aFilePath, int aSourceX, int aSourceY, int aWidth, int aHeight, Vector2 aPosition)
{
	mPosition = aPosition;
	mSourceRect.x = aSourceX;
	mSourceRect.y = aSourceY;
	mSourceRect.width = aWidth;
	mSourceRect.height = aHeight;
	mSpriteSheet = LoadTexture(aFilePath.c_str());
}

Vector2 Sprite::getPosition()
{
	return mPosition;
}

void Sprite::draw(Vector2 aPosition) {
	DrawTextureRec(mSpriteSheet, mSourceRect, aPosition, RAYWHITE);
}
