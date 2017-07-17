#pragma once

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

class AudioManager
{
private:
	bool isPlaying;
public:
	void init();
	void playBGM(char*, bool);
	void playSFX(char*, bool);
	void volUp(char*);
	void volDwn(char*);
	void pauseBGM();
	void stopBGM();

	float getVolume();

	AudioManager();
	~AudioManager();
};

