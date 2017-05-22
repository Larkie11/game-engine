#pragma once
#include "cocos2d.h"

using namespace cocos2d;
#include <string>



class GameChar
{
private: 
	cocos2d::Sprite* mainSprite;
	int intDir;
	float fSpeed;
	Vec2 mLoc;
	Vec2 mLocInc;
	GLProgram* charEffect;
	std::string tag;
	int health;
	float defaultAttackTimer;
	float attackTimer;
	int damage;
public: 
	void init(const char*, const char*, float, float, std::string, int, float, int);
	void MoveChar(int);
	void MoveCharByCoord(float, float);
	void Update(float);
	void Stop();
	void Left();
	void Right();
	bool move;
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
};