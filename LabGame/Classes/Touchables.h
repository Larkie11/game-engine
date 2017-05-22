#pragma once
#include "cocos2d.h"

using namespace cocos2d;
#include <string>
#include <vector>

class Touchables
{
public: 
	enum Types
	{
		T_SUMMONBUT1,
		T_SUMMONBUT2,
		T_SUMMONBUT3,

		T_MAX,
	};

	void init(const char*, const char*, float, float, Types);
	void Update(float);
	virtual bool checkMouseDown(Event *event);
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	void SetText(std::string text, float scale, std::string font);
	std::string GetTag()
	{
		return tag;
	}
	Types GetType()
	{
		return t;
	}
	Touchables();
	~Touchables();
	cocos2d::Sprite* getSprite(void)
	{
		return mainSprite;
	}

private:
	cocos2d::Sprite* mainSprite;
	int intDir;
	float fSpeed;
	Vec2 mLoc;
	Vec2 mLocInc;
	GLProgram* charEffect;
	std::string tag;
	Types t;
};