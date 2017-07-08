#include "PlayerMonsterDatabase.h"
#include <sstream>>
#include <iostream>
#include <fstream>
void PlayerMonsterDatabase::ReadFileSize(string fileName)
{
	std::string line;
	std::ifstream myfile(fileName);
	string op;
	std::stringstream oss;
	while (std::getline(myfile, line))
	{
		++number_of_lines;
		oss.clear();
		oss << line;
	}
	this->fileName = fileName;
	std::cout << "Number of lines in text file: " << number_of_lines << op;
	myfile.close();
}
void PlayerMonsterDatabase::PassInData()
{
	std::ifstream myfile(fileName);
	std::stringstream oss;
	string temp;
	myfile.clear();
	for (int i = 0; i < number_of_lines; i++)
	{
		std::getline(myfile, temp, ',');
		MonsterTypes* newMonster = new MonsterTypes;
		newMonster->type = temp;
		std::getline(myfile, temp, ',');
		newMonster->price = stoi(temp);
		std::getline(myfile, temp, ',');
		newMonster->tooltip = temp;
		std::getline(myfile, temp);
		newMonster->animationSprites = temp;
		monsterDatabase.push_back(newMonster);
	}
}
PlayerMonsterDatabase::MonsterTypes* PlayerMonsterDatabase::GetFromDatabase(string type)
{
	string a = "";
	for (std::vector<MonsterTypes*>::iterator it = monsterDatabase.begin(); it != monsterDatabase.end(); ++it) {
		
		if ((*it)->type == type)
		{
			a = (*it)->tooltip;
			return (*it);
		}
		else if (it == monsterDatabase.end() && (*it)->type != type)
		{
			return nullptr;
		}
	}
	
}
vector<PlayerMonsterDatabase::MonsterTypes*> PlayerMonsterDatabase::ReturnDatabase()
{
	return monsterDatabase;
}
bool PlayerMonsterDatabase::checkIfExist(string type)
{
	for (int i = 0; i < monsterDatabase.size(); ++i)
		if (monsterDatabase[i]->type == type)
			return true;

	return false;
}
Touchables PlayerMonsterDatabase::addIntoGame(const char* buttonSprite, const char* name, int x, int y, string tag,float scale)
{
	Touchables newTouch;
	newTouch.init(buttonSprite, name, x, y, tag,scale);
	return newTouch;
}