#pragma once
#include "cocos2d.h"

using namespace cocos2d;
#include <string>



class GameChar
{

public: 
	enum CharacterType
	{
		C_DOG,
		C_CAT,
		C_DOGENEMY,
		C_MAX,
	};
	void init(const char* sprite, const char* name, float x, float y, CharacterType type, int health, float attackTimer, int damage, float speed);
	void init(const char* sprite, const char* name, float x, float y, std::string Tag, int health, float attackTimer, int damage, float speed);

	void MoveChar(int);
	void AnimateSprite(const char* spriteFrameName,int startFrame, int frameCount, float width, float height, float delay);
	void SpriteAnimation(int, const char*);
	void MoveCharByCoord(float, float);
	void Update(float);
	void Stop();
	void Left();
	void Right();
	bool move;
	float GetSpeed()
	{
		return fSpeed;
	}
	void ResetAttackTime()
	{
		attackTimer = defaultAttackTimer;
	}
	void ReduceTimer(float delta)
	{
		attackTimer -= delta;
	}
	int GetDamage()
	{
		return damage;
	}
	void MinusHealth(int minus)
	{
		health -= minus;
	}
	CharacterType GetType()
	{
		return charType;
	}
	std::string GetTag()
	{
		return tag;
	}
	int GetHealth()
	{
		return health;
	}
	float GetAttackTimer()
	{
		return attackTimer;
	}
	void RemoveSprite()
	{
		mainSprite->removeFromParent();
		mainSprite = nullptr;
	}
	GameChar();
	~GameChar();
	cocos2d::Sprite* getSprite(void)
	{
		if(mainSprite != nullptr)
		return mainSprite;
		else return nullptr;
	}

	enum States
	{
		MOVE,
		STOP,
	};
private:
	cocos2d::Sprite* mainSprite;
	//cocos2d::Sprite* loadedSprite;
	CharacterType charType;
	int intDir;
	float fSpeed;
	Vec2 mLoc;
	Vec2 mLocInc;
	Sprite* character1;
	Vector<SpriteFrame*> walkFrames;
	Animation* walkAnimation;
	Animate* walkAction;
	GLProgram* charEffect;
	std::string tag;
	int health;
	float defaultAttackTimer;
	float attackTimer;
	int damage;
};