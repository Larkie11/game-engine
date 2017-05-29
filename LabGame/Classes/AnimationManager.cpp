#include "AnimationManager.h"

void AnimationManager::PlayAnimation(Sprite* sprite, const char* spriteFrameName, int startFrame, int frameCount, float width, float height, float delay)
{
	Vector<SpriteFrame*> animationFrames;
	animationFrames.reserve(frameCount);

	for (int i = startFrame; i < frameCount; i++)
	{
		std::string frameNumber = StringUtils::format("%d", i);

		std::string frameName = spriteFrameName + frameNumber + ".png";
		animationFrames.pushBack(SpriteFrame::create(frameName, Rect(0, 0, width, height)));
	}

	Animation* animation = Animation::createWithSpriteFrames(animationFrames, 0.1f);
	Animate* animated = Animate::create(animation);

	sprite->runAction(RepeatForever::create(animated));
}