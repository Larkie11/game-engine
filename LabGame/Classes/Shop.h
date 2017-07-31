#ifndef __SHOP_SCENE_H__
#define __SHOP_SCENE_H__

#include "cocos2d.h"
#include "Character.h"
#include "Touchables.h"

using namespace cocos2d;
#include <vector>
#include <string>

using std::vector;
using std::string;

class Shop : public cocos2d::Layer
{
	struct ShopItems
	{
		string type;
		int price;
		string tooltip;
		string spriteImage;
	};
private:
	Vec2 mLoc;
	Vec2 mLocInc;
	Touchables* a;
	int currency;
	Label* playerGold;
	GameChar* b;
	GLProgram* proPostProcess;
	RenderTexture *rendtex;
	vector<string> Inventory;

	Sprite* rendtexSprite;
	Sprite* backgroundSprite;
	Sprite* sprite;
	Size visibleSize;
	vector<Touchables*> touchableSprites;
	vector<ShopItems*> shopItems;
	Label* label;
	int moveDir;
	Label* label2;
	vector<GameChar*> monsters;
	vector<GameChar*> enemyMonsters;
	//Testing labels to debug
	Label* health1;
	Label* health2;
	GLProgram* shaderCharEffect;
	GLProgramState* state;
	int number_of_lines = 0;
	//PlayerMonsterDatabase database;
public:
	static cocos2d::Scene* createScene();
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* e);
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* e);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);

	virtual void onMouseUp(Event *event);
	virtual void onMouseMove(Event *event);

	void ReadFileSize();
	void PassInShopItems();

	virtual bool init();
	virtual void update(float);
	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);


	GameChar* GetPlayer()
	{
		if (b != nullptr)
			return b;
	}

	// implement the "static create()" method manually
	CREATE_FUNC(Shop);
};

#endif // __MENU_SHOP_H__

#pragma once
