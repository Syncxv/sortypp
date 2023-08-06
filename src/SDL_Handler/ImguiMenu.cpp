#include "ImguiMenu.h"

ImguiMenu::ImguiMenu(SDL_Handler* handler) {
	m_handler = handler;
	Initalize();
}

ImguiMenu::~ImguiMenu() {
	Destroy();
}

void ImguiMenu::Initalize() {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	// Setup Platform/Renderer backends
	ImGui_ImplSDL2_InitForSDLRenderer(m_handler->window, m_handler->renderer);
	ImGui_ImplSDLRenderer2_Init(m_handler->renderer);

	clear_color = ImVec4(0.0f, 0.0f, 0.0f, 0.00f);

	m_handler->RegisterCallBack(m_handler->CUSTOM_ALL, [this](SDL_Event& event) {
		ImGui_ImplSDL2_ProcessEvent(&event);
	});

}

void ImguiMenu::Destroy() {
	ImGui_ImplSDLRenderer2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	SDL_DestroyRenderer(m_handler->renderer);
	SDL_DestroyWindow(m_handler->window);
	SDL_Quit();
}

void ImguiMenu::Update() {
	// Start the Dear ImGui frame
	ImGui_ImplSDLRenderer2_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	ImGui::ShowDemoWindow();

	ImGui::Render();
//	SDL_RenderSetScale(m_handler->renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
//	SDL_SetRenderDrawColor(m_handler->renderer, (Uint8)(clear_color.x * 255), (Uint8)(clear_color.y * 255), (Uint8)(clear_color.z * 255), (Uint8)(clear_color.w * 255));
//	SDL_RenderClear(m_handler->renderer);
	ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
	//SDL_RenderPresent(m_handler->renderer);
}
