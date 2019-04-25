#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite() {}

AnimatedSprite::AnimatedSprite(const std::string &aFilePath, int aSourceX, int aSourceY, int aWidth, int aHeight, Vector2 aPosition, float aTimeToUpdate) :
Sprite(aFilePath, aSourceX, aSourceY, aWidth, aHeight, aPosition) {
	mFrameIndex = 0;
	mTimeToUpdate = aTimeToUpdate;
	mCurrentAnimation = "";
}

void AnimatedSprite::addAnimation(int aFrames, bool aLoopOnRow, float aPosX, float aPosY, std::string aName, float aWidth, float aHeight) {
	std::vector<Rectangle> lRectangles;
	for (int i = 0; i < aFrames; i++) {
		Rectangle lNewRect;

		if (aLoopOnRow) 
			lNewRect = { (i + aPosX) * aWidth, aPosY, aWidth, aHeight };
		else
			lNewRect = { aPosX, (i + aPosY) * aHeight, aWidth, aHeight };

		lRectangles.push_back(lNewRect);
	}
	mAnimations.insert(std::pair<std::string, std::vector<Rectangle> >(aName, lRectangles));
}

void AnimatedSprite::playAnimation(std::string aAnimation) {
	if (mCurrentAnimation != aAnimation) {
		mCurrentAnimation = aAnimation;
		mFrameIndex = 0;
	}
}

void AnimatedSprite::update(float aFrameTime) {
	mFrameTime += aFrameTime;
	if (mFrameTime >= mTimeToUpdate) {
		mFrameTime = 0.0f;

		if (mFrameIndex < mAnimations[mCurrentAnimation].size() - 1)
			mFrameIndex++;
		else
			mFrameIndex = 0;
	}

	mSourceRect = mAnimations[mCurrentAnimation][mFrameIndex];
}