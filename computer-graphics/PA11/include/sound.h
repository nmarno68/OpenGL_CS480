#ifndef WIZARD_DUEL_SOUND_H
#define WIZARD_DUEL_SOUND_H
#include "graphics_headers.h"

const int NUM_BUFFERS = 10;
const int NUM_SOURCES = 10;

class SoundManager
{
public:
	SoundManager(){
    SDL_Init(SDL_INIT_AUDIO);
    engineIsRunning = true;
  }
	~SoundManager(){
    if (engineIsRunning)
    {
      SDL_FreeWAV(wavBuffer);
      engineIsRunning = false;
    }
    SDL_CloseAudioDevice(deviceId);
  }
	void LoadSound(std::string path){
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
	void PlaySound(){
    if(engineIsRunning)
    {
      SDL_PauseAudioDevice(deviceId, 0);
      //SDL_Delay(200);
    }
  }
	void PauseSound(){
    if(engineIsRunning)
    {
      SDL_PauseAudioDevice(deviceId, 1);
      SDL_Delay(200);
    }
  }
private:
	SDL_AudioSpec wavSpec;
	Uint32 wavLength;
	Uint8 *wavBuffer;
	SDL_AudioDeviceID deviceId;

	bool engineIsRunning;
};

#endif //WIZARD_DUEL_SOUND_H
