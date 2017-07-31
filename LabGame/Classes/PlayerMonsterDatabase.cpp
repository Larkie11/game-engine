#include "PlayerMonsterDatabase.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>


PlayerMonsterDatabase* PlayerMonsterDatabase::dataInstance = 0;

void PlayerMonsterDatabase::ReadFileSize(string fileName)
{
	std::string line;
	ssize_t fileSize = 0;
	unsigned char * fileContents = NULL;
	string thisLine, result, fullPath, contents;

	fullPath = FileUtils::getInstance()->fullPathForFilename(fileName.c_str());
	fileContents = FileUtils::getInstance()->getFileData(fullPath.c_str(),"r",&fileSize);
	contents.append((char *)fileContents);

	std::istringstream fileStringStream(contents);
	string op;
	std::stringstream oss;
	while (std::getline(fileStringStream, line))
	{
		++number_of_lines;
		oss.clear();
		oss << line;
	}
	this->fileName = fileName;
	std::cout << "Number of lines in text file: " << number_of_lines << op;
}
void PlayerMonsterDatabase::PassInData()
{
	std::string line;
	ssize_t fileSize = 0;
	unsigned char * fileContents = NULL;
	string thisLine, result, fullPath, contents;

	fullPath = FileUtils::getInstance()->fullPathForFilename(fileName.c_str());
	fileContents = FileUtils::getInstance()->getFileData(fullPath.c_str(), "r", &fileSize);
	contents.append((char *)fileContents);

	std::istringstream fileStringStream(contents);
	for (int i = 0; i < number_of_lines; i++)
	{
		std::getline(fileStringStream, line, ',');
		MonsterTypes* newMonster = new MonsterTypes;
		newMonster->type = line;
		std::getline(fileStringStream, line, ',');
		newMonster->health = atoi(line.c_str());
		std::getline(fileStringStream, line, ',');
		newMonster->tooltip = line;
		std::getline(fileStringStream, line, ',');
		newMonster->animationSprites = line;
		std::getline(fileStringStream, line, ',');
		newMonster->attackSprite = line;
		std::getline(fileStringStream, line, ',');
		newMonster->spriteCount = atoi(line.c_str());
		std::getline(fileStringStream, line, ',');
		newMonster->spriteX = atoi(line.c_str());
		std::getline(fileStringStream, line, ',');
		newMonster->spriteY = atoi(line.c_str());
		std::getline(fileStringStream, line, ',');
		newMonster->goldNeededShop = atoi(line.c_str());
		std::getline(fileStringStream, line, ',');
		newMonster->goldNeededGame = atoi(line.c_str());
		std::getline(fileStringStream, line, ',');
		newMonster->damage = atoi(line.c_str());
		std::getline(fileStringStream, line);
		newMonster->speed = atoi(line.c_str());
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
