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

Vector2 Sprite::getPosition(){
	return mPosition;
}

void Sprite::setPosition(Vector2 aPosition) {
	mPosition = aPosition;
}

const sides::Side Sprite::getCollisionSide(Rectangle aOtherRect) const {
	
	int lAmtRight, lAmtLeft, lAmtTop, lAmtBottom;
	lAmtRight = getCollisionRect().x + getCollisionRect().width - aOtherRect.x;
	lAmtLeft = aOtherRect.x + aOtherRect.width - getCollisionRect().x;
	lAmtTop = aOtherRect.y + aOtherRect.height - getCollisionRect().y;
	lAmtBottom = getCollisionRect().y + getCollisionRect().height - aOtherRect.y;

	int lVals[4] = { abs(lAmtRight), abs(lAmtLeft), abs(lAmtTop), abs(lAmtBottom) };
	int lLowest = lVals[0];

	for (int i = 0; i < 4; i++)
		if (lVals[i] < lLowest)
			lLowest = lVals[i];
	
	return
		lLowest == abs(lAmtRight) ? sides::RIGHT :
		lLowest == abs(lAmtLeft) ? sides::LEFT :
		lLowest == abs(lAmtTop) ? sides::TOP :
		lLowest == abs(lAmtBottom) ? sides::BOTTOM :
		sides::NONE;

}

void Sprite::draw(Vector2 aPosition) {
	mCollisionRect = { aPosition.x, aPosition.y, mSourceRect.width, mSourceRect.height };
	DrawTextureRec(mSpriteSheet, mSourceRect, aPosition, RAYWHITE);
}
