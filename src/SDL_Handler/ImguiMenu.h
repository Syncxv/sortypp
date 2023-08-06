#pragma once
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>
#include <imgui.h>

#include "SDL_Handler/SDL_Handler.h"

class ImguiMenu
{

public:
	ImguiMenu(SDL_Handler* handler);
	~ImguiMenu();

	void Initalize();
	void Destroy();

	void Update();

	ImGuiIO io;
	ImVec4 clear_color;

private:
	SDL_Handler* m_handler;
};

