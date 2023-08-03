#include "Visualizer.h"


Visualizer::Visualizer(SDL_Handler* handler){
	m_handler = handler;
	m_lastSortStep = std::chrono::high_resolution_clock::now();	

	InitalizeArray();
	Shuffle();

	m_callbackIds.push_back(m_handler->RegisterCallBack(SDL_KEYDOWN, [this](SDL_Event& event) {
		if (event.key.keysym.sym == SDLK_RETURN) {
			std::cout << "BUBBLE SORTING TIME" << std::endl;
			isSorting = true;
		}

		if (event.key.keysym.sym == SDLK_s && !isSorting) {
			Shuffle();
		}
	}));

	m_callbackIds.push_back(m_handler->RegisterCallBack(SDL_WINDOWEVENT, [this](SDL_Event& event) {
		if (event.window.event == SDL_WINDOWEVENT_RESIZED && !isSorting) {
			std::cout << "AYO" << std::endl;
			InitalizeArray();
			Shuffle();
		}
	}));

}

void Visualizer::InitalizeArray() {
	m_array.clear();

	int width = m_handler->GetWindowWidth();
	int arrayLength = floor(width / lineWidth);

	for (int i = 0; i < arrayLength; ++i) {
		m_array.push_back(i);
	}
	std::cout << m_array.size() << std::endl;
}

Visualizer::~Visualizer() {
	for (size_t& id : m_callbackIds) {
		m_handler->UnregisterCallback(id);
	}
}

void Visualizer::Update() {
	if (isSorting) {
		auto now = std::chrono::high_resolution_clock::now();

		auto diff = std::chrono::duration<double>(now - m_lastSortStep);
		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(diff).count();

		if (elapsed >= 4) {
			BubbleSort();
			m_lastSortStep = now;
		}
	}
	for (int i = 0; i < m_array.size(); ++i) {
		SDL_Rect rect;
		rect.x = i * lineWidth;
		rect.y = m_handler->GetWindowHeight();
		rect.w = lineWidth;

		float fElement = static_cast<float>(m_array[i] + 1);
		float fSize = static_cast<float>(m_array.size());

		int res = (fElement / fSize) * m_handler->GetWindowHeight();
		rect.h = -res;


		if (currentSortingIndex <= m_array.size() && i == m_array[currentSortingIndex])
			SDL_SetRenderDrawColor(m_handler->renderer, 255, 0, 0, 255);
		else
			SDL_SetRenderDrawColor(m_handler->renderer, 255, 255, 255, 255);

		SDL_RenderFillRect(m_handler->renderer, &rect);

		SDL_SetRenderDrawColor(m_handler->renderer, 0, 0, 0, 255);  // Black color
		SDL_RenderDrawRect(m_handler->renderer, &rect);
	}

	SDL_RenderPresent(m_handler->renderer);
}

void Visualizer::Shuffle() {
	std::random_device rd;
	std::mt19937 g(rd());

	for (int k = 0; k < m_array.size(); ++k) {
		std::uniform_int_distribution<> dis(k, m_array.size() - 1);
		int r = dis(g);
		std::swap(m_array[k], m_array[r]);
	}
}

void Visualizer::BubbleSort() {
	static int i = 0;
	static int j = 0;

	if (i < m_array.size()) {
		if (j < m_array.size() - i - 1) {
			if (m_array[j] > m_array[j + 1]) {
				currentSortingIndex = j;
				std::swap(m_array[j], m_array[j + 1]);
			}
			++j;
		}
		else {
			j = 0;
			++i;
		}
	}
	else {
		i = 0;
		j = 0;
		isSorting = false;
	}
}
