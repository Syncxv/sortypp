#include <iostream>
#include <SDL.h>
#include "SDL_Handler/SDL_Handler.h"
#include "Visualizer/Visualizer.h"
int main(int argc, char* argv[]) {

	SDL_Handler handler;
	Visualizer visualizer{ &handler };

	while (handler.isRunning) {
		SDL_SetRenderDrawColor(handler.renderer, 0, 0, 0, 255);
		SDL_RenderClear(handler.renderer);

		visualizer.Update();
		handler.PollEvents();
	}
	
	return 0;
}