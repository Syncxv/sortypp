#include "SDLBeeper.h"

#include <iostream>

Sint16 format(double sample, double amplitude);
double tone(double hz, unsigned long time);

SDLBeeper::SDLBeeper() {
	Initalize();
}

SDLBeeper::~SDLBeeper() {
	Destroy();
}

void SDLBeeper::Initalize() {
	spec = {
		.freq = FREQUENCY,
		.format = AUDIO_S16SYS, // Signed 16 bit integer format
		.channels = 1,
		.samples = 4096, // The size of each "chunk"
		.callback = audioCallback, // user-defined function that provides the audio data
		.userdata = this // an argument to the callback function (we dont need any)
	};

	audioDevice = SDL_OpenAudioDevice(NULL, 0, &spec, NULL, 0);
}


void SDLBeeper::Destroy() {
	SDL_CloseAudioDevice(audioDevice);
}

void SDLBeeper::audioCallback(void* userdata, Uint8* stream, int len) {
	SDLBeeper* beeper = static_cast<SDLBeeper*>(userdata);
	beeper->playBuffer(stream, len);
}

void SDLBeeper::playBuffer(unsigned char* stream, int len) {
	std::cout << "Playing buffer..." << std::endl;

	// Silence the whole stream in case we don't touch some parts of it
// This fills the stream with the silence value (almost always just 0)
// SDL implements the standard library (SDL_memset, SDL_memcpy etc.) to support more platforms
	SDL_memset(stream, spec.silence, len);

	// Dividing the stream size by 2 gives us the real length of the buffer (our format is 2 bytes per sample)
	len /= 2;
	// Prevent overflows (if we get to the end of the sound buffer, we don't want to read beyond it)
	len = (m_bufferPos + len < BUFFER_LEN ? len : BUFFER_LEN - m_bufferPos);

	// If we are at the end of the buffer, keep the silence and return
	if (len == 0) return;

	// Copy the samples from the current position in the buffer to the stream
	// Notice that the length gets multiplied back by 2 because we need to specify the length IN BYTES
	SDL_memcpy(stream, buffer + m_bufferPos, len * 2);

	// Move the buffer position
	m_bufferPos += len;
}

void SDLBeeper::beep(double hz) {
	m_currentHz = hz;
	fillBufferWithTone(m_currentHz);
	m_bufferPos = 0; // Reset buffer position for the callback.
	SDL_PauseAudioDevice(audioDevice, 0); // Start playing the sound.
	SDL_Delay(BUFFER_DURATION_MS);
}

void SDLBeeper::stop() {
	SDL_PauseAudioDevice(audioDevice, 1);
}

void SDLBeeper::fillBufferWithTone(double hz) {
	int samples_to_generate = (BUFFER_DURATION_MS * FREQUENCY) / 1000;
	for (int i = 0; i < samples_to_generate; i++) {
		buffer[i] = format(tone(hz, i), 0.5);
	}
}


Sint16 format(double sample, double amplitude) {
	// 32567 is the maximum value of a 16 bit signed integer (2^15-1)
	return (Sint16)(sample * 32567 * amplitude);
}

// Generate a sine wave
double tone(double hz, unsigned long time) {
	return sin(time * hz * M_PI * 2 / FREQUENCY);
}
