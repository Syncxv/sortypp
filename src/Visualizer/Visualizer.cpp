#include "Visualizer.h"


Visualizer::Visualizer(SDL_Handler* handler){
	m_handler = handler;
	m_lastOperationTime = std::chrono::high_resolution_clock::now();	

	InitalizeArray();
	Shuffle();

	m_callbackIds.push_back(m_handler->RegisterCallBack(SDL_KEYDOWN, [this](SDL_Event& event) {
		if (event.key.keysym.sym == SDLK_RETURN) {
			ResetOperations();
			BubbleSort();
		}

		if (event.key.keysym.sym == SDLK_s && !isSorting) {
			Shuffle();
		}
	}));

	m_callbackIds.push_back(m_handler->RegisterCallBack(SDL_WINDOWEVENT, [this](SDL_Event& event) {
		if (event.window.event == SDL_WINDOWEVENT_RESIZED && !isSorting) {
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

void Visualizer::Shuffle() {
	ResetOperations();
	std::random_device rd;
	std::mt19937 g(rd());

	for (int k = 0; k < m_array.size(); ++k) {
		std::uniform_int_distribution<> dis(k, m_array.size() - 1);
		int r = dis(g);
		std::swap(m_array[k], m_array[r]);
	}
}


Visualizer::~Visualizer() {
	for (size_t& id : m_callbackIds) {
		m_handler->UnregisterCallback(id);
	}
}

void Visualizer::Update() {
	auto now = std::chrono::high_resolution_clock::now();
	auto diff = std::chrono::duration<double>(now - m_lastOperationTime);
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(diff).count();

	if (isSorting && elapsed >= delay && m_currentOperationIndex < m_operations.size()) {
		Operation& op = m_operations[m_currentOperationIndex];
		switch (op.type) {
		case OperationType::COMPARE:
			// Highlight the two indices being compared.
			//...
			break;
		case OperationType::SWAP:
			// Swap and highlight the two indices.
			std::swap(m_array[op.indexA], m_array[op.indexB]);
			std::cout << "PLAYING INDEX A: " << op.indexA << std::endl;
			std::thread t(&Visualizer::playSwap, this, std::ref(op.indexA));
			t.detach();
			break;
		}
		m_currentOperationIndex++;
        m_lastOperationTime = now;
	}
	if (isSorting && m_currentOperationIndex >= m_operations.size())
		StopSort();

	RenderLines();
}


void Visualizer::RenderLines() {
	for (int i = 0; i < m_array.size(); ++i) {
		SDL_Rect rect;
		rect.x = i * lineWidth;
		rect.y = m_handler->GetWindowHeight();
		rect.w = lineWidth;

		float fElement = static_cast<float>(m_array[i] + 1);
		float fSize = static_cast<float>(m_array.size());

		int res = (fElement / fSize) * m_handler->GetWindowHeight();
		rect.h = -res;


		if (currentSortingIndex < m_array.size() && i == m_array[currentSortingIndex])
			SDL_SetRenderDrawColor(m_handler->renderer, 255, 0, 0, 255);
		else
			SDL_SetRenderDrawColor(m_handler->renderer, 255, 255, 255, 255);

		SDL_RenderFillRect(m_handler->renderer, &rect);

		SDL_SetRenderDrawColor(m_handler->renderer, 0, 0, 0, 255);  // Black color
		SDL_RenderDrawRect(m_handler->renderer, &rect);
	}
}


void Visualizer::StartSort() {
	ResetOperations();
	const char* algo = algos[selected];
	if (algo == "Bubble Sort") {
		BubbleSort();
	}
	else if (algo == "Insertion Sort") {
		InsertionSort();
	}
	isSorting = true;
}

void Visualizer::Resume() {
	isSorting = true;
}

void Visualizer::StopSort() {
	isSorting = false;
	beeper.stop();
}

void Visualizer::ResetOperations() {
	m_operations.clear();
	m_currentOperationIndex = 0;
}


void Visualizer::playSwap(int index) {
	if (!m_handler->isRunning || isSorting)
		beeper.stop();
	beeper.beep((double)(index * 20));
}

void Visualizer::BubbleSort() {
	std::vector<int> coolArr = m_array;
	int n = coolArr.size();
	
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			m_operations.push_back({ OperationType::COMPARE, j, j + 1 });
			if (coolArr[j] > coolArr[j + 1]) {
				m_operations.push_back({ OperationType::SWAP, j, j + 1 });
				std::swap(coolArr[j], coolArr[j + 1]);
			}
		}
	}
}



void Visualizer::InsertionSort() {
	std::vector<int> coolArr = m_array;
	for (int i = 1; i < coolArr.size(); i++) {
		int current = coolArr[i];
		int j = i - 1;

		// Record the comparison operation
		m_operations.push_back({ OperationType::COMPARE, j, i });

		while (j >= 0 && coolArr[j] > current) {
			// Record the swap operation
			m_operations.push_back({ OperationType::SWAP, j, j + 1 });
			coolArr[j + 1] = coolArr[j];
			j--;

			if (j >= 0) {
				// Record the next comparison operation
				m_operations.push_back({ OperationType::COMPARE, j, i });
			}
		}

		coolArr[j + 1] = current;
	}
}
