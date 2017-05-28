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
		T_INSTRUCTIONS,
		T_EXIT,
		T_BACK,
		T_GOLDUPGRADE,
		T_SHOP1,
		T_SHOP2,
		T_SHOP3,
		T_MAX,
	};

	void init(const char*, const char*, float, float, Types);
	void Update(float);
	void SetDisabled(bool disabled);
	virtual bool checkMouseDown(Event *event);
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	void SetText(std::string text, float scale, std::string font, cocos2d::Color3B & color, float offsetx, float offsety);
	void SetToolTip(std::string text, const char* sprite, int opacity, float offsetx, float offsety, float scale);
	void SetImage(const char* sprite, const char* name, float scale);
	bool GetDisabled();
	void AnimateImage(const char* spriteFrameName, int startFrame, int frameCount, float width, float height);

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
	Sprite* GetImg(const char* image)
	{
		Sprite *s = dynamic_cast<Sprite*>(mainSprite->getChildByName(image));
		if (s != nullptr)
			return s;
		else
			return nullptr;
	}
	Sprite* GetToolTip()
	{
		Sprite *s = dynamic_cast<Sprite*>(mainSprite->getChildByName("ToolTip"));
		if (s != nullptr)
			return s;
		else
			return nullptr;
	}
	void StopAnimation()
	{
		if (playingAnimation)
		{
			GetImg(imageName)->stopAllActions();
		}
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
	bool playingAnimation = false;
	cocos2d::Sprite* mainSprite;
	int intDir;
	float fSpeed;
	Vec2 mLoc;
	Vec2 mLocInc;
	const char* imageName;
	GLProgram* charEffect;
	std::string tag;
	Types t;
	bool disabled;
	cocos2d::Color3B color;
};