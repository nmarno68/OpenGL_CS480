#include "sound.h"

SoundManager::SoundManager()
{
	SDL_Init(SDL_INIT_AUDIO);
	engineIsRunning = true;
}

SoundManager::~SoundManager()
{
	if (engineIsRunning)
	{
		SDL_FreeWAV(wavBuffer);
		engineIsRunning = false;
	}
	SDL_CloseAudioDevice(deviceId);
}

void SoundManager::LoadSound(std::string path)
{
	if(!SDL_LoadWAV(path.c_str(), &wavSpec, &wavBuffer, &wavLength))
	{
		engineIsRunning = false;
	}
	else
	{
		deviceId = SDL_OpenAudioDevice( NULL, 0, &wavSpec, NULL, SDL_AUDIO_ALLOW_ANY_CHANGE );
		SDL_QueueAudio(deviceId, wavBuffer, wavLength);
	}
}

void SoundManager::PlaySound()
{
	if(engineIsRunning)
	{
		SDL_PauseAudioDevice(deviceId, 0);
		//SDL_Delay(200);
	}
}
void SoundManager::PauseSound()
{
	if(engineIsRunning)
	{
		SDL_PauseAudioDevice(deviceId, 1);
		SDL_Delay(200);
	}
}
