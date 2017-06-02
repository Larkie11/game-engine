#ifndef SCENE_MANAGER_H
#define SCEME_MANAGER_H

#include <iostream>
#include <fstream>
#include <string>
#include "cocos2d.h"
using std::string;
using std::ifstream;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();
	void ReadFile(string filePath);
	string getFont();
	string getBackground();
	string getButtonClickSound();

	static SceneManager* getInstance()
	{
		static SceneManager* instance;
		return instance;
	}

private:
	string font;
	string background;
	string buttonClickSound;
};



#endif // !SCENE_MANAGEMENT_H
