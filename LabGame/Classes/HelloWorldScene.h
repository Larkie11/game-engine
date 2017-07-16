#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Character.h"
#include "Touchables.h"
#include "AudioManager.h"

using namespace cocos2d;
#include <vector>
using std::vector;

class HelloWorld : public cocos2d::Layer
{

private:
	Vec2 mLoc;
	Vec2 mLocInc;
	Touchables* a;
	GameChar* b;
	GLProgram* proPostProcess;
	vector<string> Inventory;
	AudioManager* audioMng;
	RenderTexture *rendtex;
	Sprite* rendtexSprite;
	Sprite* backgroundSprite;
	Sprite* character1, character2;
	Size visibleSize;
	vector<Touchables*> touchableSprites;
	vector<Touchables*> summonButtons;

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
	int high_score = 0;
	Label* gold;
	Label* incomeSpeed;
	int money = 0;
	float speedOfIncome = 60;
	bool inContact = false;
	float spawnTimer;
	float dt;

public:
    static cocos2d::Scene* createScene();
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* e);
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* e);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);

	virtual void onMouseUp(Event *event);
	virtual void onMouseMove(Event *event);
	virtual bool onInContact(PhysicsContact& contact);

	virtual bool onContactBegin(PhysicsContact& contact);
    virtual bool init();
	virtual void update(float);
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);


	GameChar* GetPlayer()
	{
		if(b!= nullptr)
		return b;
	}
	
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
