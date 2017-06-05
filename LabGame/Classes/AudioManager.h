#pragma once

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

class AudioManager 
{
public:
	void init();
	void playBGM(const char*, bool);
	void playSFX(const char*, bool);
	void pauseBGM();
	void stopBGM();

	AudioManager();
	~AudioManager();
};

