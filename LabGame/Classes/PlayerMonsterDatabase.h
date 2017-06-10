#pragma once
#include <string>
#include <vector>
#include "Touchables.h"
using std::string;
using std::vector;

class PlayerMonsterDatabase
{
	
public:
	struct MonsterTypes
	{
		Touchables a;
		string type;
		int price;
		string tooltip;
		string animationSprites;
	};

	void ReadFileSize(string fileName);
	void PassInData();
	MonsterTypes* GetFromDatabase(string type);
	vector<MonsterTypes*> ReturnDatabase();
	Touchables addIntoGame(const char* buttonSprite, const char* name, int x, int y, string tag,float scale);
	bool checkIfExist(string type);

private:
	vector<MonsterTypes*> monsterDatabase;
	string fileName;
	int number_of_lines = 0;
};