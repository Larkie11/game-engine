#include "SceneManager.h"

SceneManager::SceneManager()
{

}

SceneManager::~SceneManager()
{

}


void SceneManager::ReadFile(string filePath)
{
	ifstream inputFile(filePath);
	string firstLine;
	string secondLine;

	while (!inputFile.eof())
	{
		getline(inputFile, font);
		getline(inputFile, background);
		getline(inputFile, buttonClickSound);
		//background = secondLine.c_str();

	}
	//inputFile.close();
}

string SceneManager::getFont()
{
	return font;
}

string SceneManager::getBackground()
{
	return background;
}

string SceneManager::getButtonClickSound()
{
	return buttonClickSound;
}
