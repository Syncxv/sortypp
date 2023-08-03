#pragma once
#include <SDL.h>
#include <iostream>
#include <map>
#include <functional>
#include <vector>

class SDL_Handler {
public:
	SDL_Handler();
	~SDL_Handler();

	bool Initalize();
	void Destroy();

	int GetWindowHeight();
	int GetWindowWidth();

	void PollEvents();

	size_t RegisterCallBack(SDL_EventType eventType, std::function<void(SDL_Event&)> callback);
	void UnregisterCallback(SDL_EventType eventType, size_t index);


	SDL_Window* window;
	SDL_Renderer* renderer;

	bool isRunning = true;
private:

	std::map<SDL_EventType, std::vector<std::function<void(SDL_Event&)>>> m_eventCallbacks;
	FILE* m_stdout;

};

