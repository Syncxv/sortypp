#pragma once
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
#include <thread>
#include <chrono>


#include "../SDL_Handler/SDL_Handler.h"

class Visualizer {
public:
	Visualizer(SDL_Handler* handler);
	~Visualizer();

	void Update();

	void InitalizeArray();
	void Shuffle();
	void BubbleSort();

	int lineWidth = 20;
	bool isSorting = false;
	int currentSortingIndex;
private:
	std::vector<int> m_array;
	SDL_Handler* m_handler;
	std::chrono::high_resolution_clock::time_point m_lastSortStep;

};

