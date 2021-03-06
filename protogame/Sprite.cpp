#include "Sprite.h"

Sprite::Sprite() {}

Sprite::Sprite(const std::string &aFilePath, int aSourceX, int aSourceY, int aWidth, int aHeight, Vector2 aPosition)
{
	mPosition = aPosition;
	mSourceRect.x = (float)aSourceX;
	mSourceRect.y = (float)aSourceY;
	mSourceRect.width = (float)aWidth;
	mSourceRect.height = (float)aHeight;
	mSpriteSheet = LoadTexture(aFilePath.c_str());
}

Vector2 Sprite::getPosition(){
	return mPosition;
}

void Sprite::setPosition(Vector2 aPosition) {
	mPosition = aPosition;
}

const Sides::Side Sprite::getCollisionSide(Rectangle aOtherRect) const {
	
	int lAmtRight, lAmtLeft, lAmtTop, lAmtBottom;
	lAmtRight = (int)(getCollisionRect().x + getCollisionRect().width - aOtherRect.x);
	lAmtLeft = (int)(aOtherRect.x + aOtherRect.width - getCollisionRect().x);
	lAmtTop = (int)(aOtherRect.y + aOtherRect.height - getCollisionRect().y);
	lAmtBottom = (int)(getCollisionRect().y + getCollisionRect().height - aOtherRect.y);

	int lVals[4] = { abs(lAmtRight), abs(lAmtLeft), abs(lAmtTop), abs(lAmtBottom) };
	int lLowest = lVals[0];

	for (int i = 0; i < 4; i++)
		if (lVals[i] < lLowest)
			lLowest = lVals[i];
	
	return
		lLowest == abs(lAmtRight) ? Sides::RIGHT :
		lLowest == abs(lAmtLeft) ? Sides::LEFT :
		lLowest == abs(lAmtTop) ? Sides::TOP :
		lLowest == abs(lAmtBottom) ? Sides::BOTTOM :
		Sides::NONE;

}

void Sprite::draw() {
	mCollisionRect = { mPosition.x, mPosition.y, mSourceRect.width, mSourceRect.height };
	DrawTextureRec(mSpriteSheet, mSourceRect, mPosition, RAYWHITE);
}
