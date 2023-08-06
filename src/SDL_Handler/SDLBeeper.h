#pragma once
#include <SDL.h>

#define BUFFER_DURATION_MS 100 // Length of the buffer in seconds
#define FREQUENCY 48000 // Samples per second
#define BUFFER_LEN ((BUFFER_DURATION_MS * FREQUENCY) / 1000) // Samples in the buffer

class SDLBeeper
{
public:
	SDLBeeper();
	~SDLBeeper();

	void Initalize();
	void Destroy();
	void playBuffer(unsigned char* stream, int len);
	static void audioCallback(void* userdata, Uint8* stream, int len);
	void beep(double hz);

	SDL_AudioSpec spec;
	SDL_AudioDeviceID audioDevice;

private:
	double m_currentHz = 440.0;
	int m_bufferPos = 0;
	Sint16 buffer[BUFFER_LEN];
	void fillBufferWithTone(double hz);


};

