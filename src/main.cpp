#include <iostream>
#include <SDL.h>
#include "SDL_Handler/SDL_Handler.h"
#include "Visualizer/Visualizer.h"
#include "ImguiMenu/ImguiMenu.h"


int main(int argc, char* argv[]) {

	SDL_Handler handler;
	Visualizer visualizer(&handler);
	ImguiMenu imguiMenu(&handler, &visualizer);

	while (handler.isRunning) {
		SDL_SetRenderDrawColor(handler.renderer, 0, 0, 0, 255);
		SDL_RenderClear(handler.renderer);

		visualizer.Update();
		imguiMenu.Update();
		handler.PollEvents();

		SDL_RenderPresent(handler.renderer);
	}

	return 0;
}
