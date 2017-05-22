#pragma once
#include "cocos2d.h"

using namespace cocos2d;
#include <string>
#include <vector>

class Touchables
{
private: 
	cocos2d::Sprite* mainSprite;
	int intDir;
	float fSpeed;
	Vec2 mLoc;
	Vec2 mLocInc;
	GLProgram* charEffect;
	std::string tag;

public: 
	void init(const char*, const char*, float, float, std::string);
	void Update(float);
	virtual bool checkMouseDown(Event *event);
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);

	std::string GetTag()
	{
		return tag;
	}
	Touchables();
	~Touchables();
	cocos2d::Sprite* getSprite(void)
	{
		return mainSprite;
	}
};