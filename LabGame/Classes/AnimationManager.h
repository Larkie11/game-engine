#pragma once
#include "cocos2d.h"
using namespace cocos2d;

class AnimationManager
{
public:
	void PlayAnimation(Sprite* sprite,const char* spriteFrameName, int startFrame, int frameCount, float width, float height, float delay);
};
