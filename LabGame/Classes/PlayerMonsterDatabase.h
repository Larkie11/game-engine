#pragma once
#include <string>
#include <vector>
#include "Touchables.h"
using std::string;
using std::vector;

//Singleton class
//Reads from file the monster file once
//Afterwards can get the values from this database
class PlayerMonsterDatabase
{
struct MonsterTypes
	{
		Touchables a;
		string type;
		int price;
		string tooltip;
		string animationSprites;
		int spriteCount;
		float spriteX;
		float spriteY;
		int goldNeededShop;
		int goldNeededGame;
		int damage;
		float speed;
	};

private:
	vector<MonsterTypes*> monsterDatabase;
	string fileName;
	int number_of_lines = 0;
	static PlayerMonsterDatabase* dataInstance;
	PlayerMonsterDatabase() {
	}

public:
	void ReadFileSize(string fileName);
	void PassInData();
	MonsterTypes* GetFromDatabase(string type);
	vector<MonsterTypes*> ReturnDatabase();
	Touchables addIntoGame(const char* buttonSprite, const char* name, int x, int y, string tag,float scale);
	bool checkIfExist(string type);
	static PlayerMonsterDatabase* getInstance()
	{
		if (dataInstance == 0)
		{
			dataInstance = new PlayerMonsterDatabase();
		}
		return dataInstance;
	}
};