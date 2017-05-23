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
		T_LEVEL1,
		T_LEVEL2,
		T_LEVEL3,
		T_SUMMONBUT1,
		T_SUMMONBUT2,
		T_SUMMONBUT3,
		T_STARTGAME,
		T_SHOP,
		T_SETTINGS,
		T_EXIT,
		T_MAX,
	};

	void init(const char*, const char*, float, float, Types);
	void Update(float);
	void SetDisabled(bool disabled);
	virtual bool checkMouseDown(Event *event);
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	void SetText(std::string text, float scale, std::string font, cocos2d::Color3B & color, float offsetx, float offsety);
	void SetImage(const char* sprite, const char* name);
	bool GetDisabled();
	cocos2d::Color3B GetDefaultTextColor()
	{
		return color;
	}
	Label* GetLabel()
	{
		Label *s = dynamic_cast<Label*>(mainSprite->getChildByName("label"));
		if (s != nullptr)
			return s;
		else
			return nullptr;
	}
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
	bool disabled;
	cocos2d::Color3B color;
};