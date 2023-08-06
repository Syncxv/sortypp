#pragma once
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>
#include <imgui.h>

#include "SDL_Handler/SDL_Handler.h"
#include "Visualizer/Visualizer.h"

class ImguiMenu {
public:
	ImguiMenu(SDL_Handler* handler, Visualizer* visualizer);
	~ImguiMenu();

	void Initalize();
	void Destroy();

	void Update();

	ImGuiIO io;

	bool isOpen = true;

private:
	SDL_Handler* m_handler;
	Visualizer* m_visualizer;
};