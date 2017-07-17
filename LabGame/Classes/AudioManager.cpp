#include "AudioManager.h"



void AudioManager::init()
{
	/*if (!Layer::init())
	{
	return false;
	}*/
	//isPlaying = false;
	auto manager = CocosDenshion::SimpleAudioEngine::getInstance();
	manager->preloadEffect("audio/click.wav");
	manager->preloadBackgroundMusic("audio/bgm.wav");
	manager->preloadBackgroundMusic("audio/bgm2.wav");
}

void AudioManager::playBGM(char * audioFile, bool repeat)
{
	auto manager = CocosDenshion::SimpleAudioEngine::getInstance();
	std::string bgmVar1 = "menu";
	std::string bgmVar2 = "game";
	if (audioFile == bgmVar1)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/bgm.wav", repeat);
		cocos2d::log("Playing background music");
		//isPlaying = true;
	}
	else if (audioFile == bgmVar2)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/bgm2.wav", repeat);
		cocos2d::log("Playing background music 2");
		//isPlaying = true;
	}
	else
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		cocos2d::log("Not Playing background music");
		//isPlaying = false;
	}

}

void AudioManager::playSFX(char *audioFile, bool repeat)
{
	auto manager = CocosDenshion::SimpleAudioEngine::getInstance();
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

void AudioManager::volUp(char* type)
{
	auto manager = CocosDenshion::SimpleAudioEngine::getInstance();
	float maxVol = 1.0f;
	float currentBGMVol = manager->getBackgroundMusicVolume();
	float currentSFXVol = manager->getEffectsVolume();
	if (type == "bgm")
	{
		if (currentBGMVol >= maxVol)
		{
			manager->setBackgroundMusicVolume(maxVol);
		}
		/*for (int x = currentBGMVol; x < maxVol; x++)
		{
		manager->setBackgroundMusicVolume(x/10);
		}*/

		manager->setBackgroundMusicVolume(currentBGMVol + 0.2);

	}
	else if (type == "sfx")
	{
		if (currentSFXVol >= maxVol)
		{
			manager->setEffectsVolume(maxVol);
		}
		for (int y = currentSFXVol; y < maxVol; y++)
		{
			manager->setEffectsVolume(y / 10);
		}
	}


}

void AudioManager::volDwn(char* type)
{
	auto manager = CocosDenshion::SimpleAudioEngine::getInstance();
	float minVol = 0.0f;
	float currentBGMVol = manager->getBackgroundMusicVolume();
	float currentSFXVol = manager->getEffectsVolume();
	if (type == "bgm")
	{
		if (currentBGMVol >= minVol)
		{
			manager->setBackgroundMusicVolume(minVol);
		}
		/*for (float x = currentBGMVol; x > minVol; x--)
		{
		manager->setBackgroundMusicVolume(x / 10);
		}*/
		manager->setBackgroundMusicVolume(currentBGMVol - 0.2);
	}
	else if (type == "sfx")
	{
		if (currentSFXVol >= minVol)
		{
			manager->setEffectsVolume(minVol);
		}
		for (float y = currentSFXVol; y > minVol; y--)
		{
			manager->setEffectsVolume(y / 10);
		}
	}
}

void AudioManager::pauseBGM()
{
	auto manager = CocosDenshion::SimpleAudioEngine::getInstance();
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	cocos2d::log("Paused background music");
}

void AudioManager::stopBGM()
{
	auto manager = CocosDenshion::SimpleAudioEngine::getInstance();
	//isPlaying = CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying();
	//if (isPlaying == true)
	//{
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(0);
	cocos2d::log("Background music stopped");
	//}

}

float AudioManager::getVolume()
{
	float bgmVol;
	auto manager = CocosDenshion::SimpleAudioEngine::getInstance();
	bgmVol = manager->getBackgroundMusicVolume();
	return bgmVol;
}

AudioManager::AudioManager()
{
}


AudioManager::~AudioManager()
{
}
