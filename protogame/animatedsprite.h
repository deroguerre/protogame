#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include "Sprite.h"
#include <map>
#include <vector>

class AnimatedSprite : public Sprite 
{
public:
	AnimatedSprite();
	AnimatedSprite(const std::string &aFilePath, int aSourceX, int aSourceY, int aWidth, int aHeight, Vector2 aPosition, float aTimeToUpdate);

	void playAnimation(std::string aAnimation);
	void update(float aFrameTime);
	void draw(Vector2 aPosition);

protected:
	float mTimeToUpdate;
	std::string mCurrentAnimation;

	virtual void setupAnimations() = 0;
	void addAnimation(int aFrames, bool aLoopOnRow, float aPosX, float aPosY, std::string aName, float aWidth, float aHeight);
	
private:
	std::map<std::string, std::vector<Rectangle>> mAnimations;
	int mFrameIndex = 0;
	float mFrameTime = 0;
};

#endif