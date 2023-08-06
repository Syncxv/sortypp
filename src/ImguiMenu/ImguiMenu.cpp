#include "ImguiMenu.h"


static void HelpMarker(const char* desc);

ImguiMenu::ImguiMenu(SDL_Handler* handler, Visualizer* visualizer) {
	m_handler = handler;
	m_visualizer = visualizer;
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

	ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(300, 150), ImGuiCond_FirstUseEver);

	if (ImGui::Begin("SORTING GANG", &isOpen)) {

        ImGui::BeginChild("Options", ImVec2(0, -ImGui::GetFrameHeightWithSpacing())); // Leave room for 1 line below us
		if (ImGui::SliderInt("Line Width", &m_visualizer->lineWidth, 0, 100)) {
			
			m_visualizer->InitalizeArray();
			m_visualizer->Shuffle();
		}
		ImGui::SameLine(); HelpMarker("CTRL+click to input value.");

		ImGui::SliderInt("Speed", &m_visualizer->speed, 1, 1090);
		ImGui::SameLine(); HelpMarker("CTRL+click to input value.\nHigher the value the slower it is");

		ImGui::Combo("Algorithm", &m_visualizer->selected, m_visualizer->items, IM_ARRAYSIZE(m_visualizer->items));
		ImGui::EndChild();

		if (ImGui::Button("Shuffle"))
			m_visualizer->Shuffle();
		ImGui::SameLine();
		if (ImGui::Button("Start"))
			m_visualizer->isSorting = true;
		ImGui::SameLine();
		if (ImGui::Button("Stop"))
			m_visualizer->isSorting = false;
		ImGui::SameLine();
	}

	ImGui::End();

	// Render the ImGui frame
	ImGui::Render();
	ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
}

static void HelpMarker(const char* desc)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::BeginItemTooltip())
	{
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}
