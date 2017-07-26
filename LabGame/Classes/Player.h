#pragma once
#include "cocos2d.h"

using namespace cocos2d;
#include <string>

class Player
{

public:
	enum PlayerCharacter
	{
		C_TOWER,
		C_DOG,
		C_CAT,
		C_ZOMBIE,
		C_MAX,
	};
	void setProgress(int);
	int getProgress();
	void setUpgrades(PlayerCharacter,int);
	int getUpgrades(PlayerCharacter);
	
	static Player* getInstance()
	{
		if (dataInstance == 0)
		{
			dataInstance = new Player();
		}
		return dataInstance;
	}

	void PassInData();
	void PassOutData();

	Player();
	~Player();
	
private:
	int progress;
	int upgLevel[(int)PlayerCharacter::C_MAX] = { 0 };
	std::string fileName;
	static Player* dataInstance;
};