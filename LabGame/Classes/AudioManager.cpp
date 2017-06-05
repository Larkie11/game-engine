#include "AudioManager.h"



void AudioManager::init()
{
	/*if (!Layer::init())
	{
		return false;
	}*/

	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/click.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("audio/bgm.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("audio/bgm2.wav");
	
}

void AudioManager::playBGM(const char * audioFile, bool repeat)
{
	std::string bgmVar1 = "menu";
	std::string bgmVar2 = "game";
	if (audioFile == bgmVar1)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/bgm", repeat);
	}
	else if (audioFile == bgmVar2)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/bgm2", repeat);
	}
	else
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	}
	
}

void AudioManager::playSFX(const char *audioFile, bool repeat)
{
	std::string sfxVar = "click";
	if (audioFile == sfxVar)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/click.wav", repeat);
	}
	else
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/click.wav", repeat);
	}
}

void AudioManager::pauseBGM()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

void AudioManager::stopBGM()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

AudioManager::AudioManager()
{
}


AudioManager::~AudioManager()
{
}
