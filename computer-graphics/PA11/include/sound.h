#ifndef WIZARD_DUEL_SOUND_H
#define WIZARD_DUEL_SOUND_H
#include "graphics_headers.h"

const int NUM_BUFFERS = 10;
const int NUM_SOURCES = 10;

class SoundManager
{
public:
	SoundManager();
	~SoundManager();
	void LoadSound(std::string path);
	void PlaySound();
	void PauseSound();
private:
	SDL_AudioSpec wavSpec;
	Uint32 wavLength;
	Uint8 *wavBuffer;
	SDL_AudioDeviceID deviceId;

	bool engineIsRunning;
};

#endif //WIZARD_DUEL_SOUND_H
