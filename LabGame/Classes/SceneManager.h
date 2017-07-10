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
private:
	static SceneManager* sceneInstance;
	string font;
	string background;
	string buttonClickSound;

public:
	SceneManager();
	~SceneManager();
	void ReadFile(string filePath);
	string getFont();
	string getBackground();
	string getButtonClickSound();

	
	static SceneManager* getInstance()
	{
		if (sceneInstance == 0)
		{
			sceneInstance = new SceneManager();
		}
		return sceneInstance;
	}

};



#endif // !SCENE_MANAGEMENT_H
