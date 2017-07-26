#include "Player.h"
#include "PlayerMonsterDatabase.h"
#include <sstream>
#include <iostream>
#include <fstream>

Player* Player::dataInstance = 0;

void Player::setProgress(int completedLvl)
{
	progress = completedLvl;
}

int Player::getProgress()
{
	return progress;
}

void Player::setUpgrades(PlayerCharacter character, int newLvl)
{
	upgLevel[(int)character] = newLvl;
}

int Player::getUpgrades(PlayerCharacter character)
{
	return upgLevel[(int)character];
}

void Player::PassInData()
{
	std::ifstream myfile(fileName);
	std::stringstream oss;
	string temp;
	//myfile.clear();
	//std::getline(myfile, temp);
	std::getline(myfile, temp, ',');
	progress = stoi(temp);
	for (int i = 0; i < PlayerCharacter::C_MAX; i++)
	{
		std::getline(myfile, temp, ',');
		upgLevel[i] = stoi(temp);
	}
		
}

void Player::PassOutData()
{
	std::ofstream myfile(fileName);
	string temp;
	if (myfile.is_open())
	{
		myfile << progress;
		myfile << ",";
		for (int i = 0; i < PlayerCharacter::C_MAX; i++)
		{
			myfile << upgLevel[i];
			myfile << ",";
		}
	}
	else
	{
		std::cout << "Open file failed";
	}
}

Player::Player()
{
	fileName = "levels/playerProgress.txt";
	progress = 0;
	//upgLevel[(int)PlayerCharacter::C_MAX] = ;
}