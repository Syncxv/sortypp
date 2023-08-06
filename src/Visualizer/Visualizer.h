#pragma once
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
#include <thread>
#include <chrono>


#include "SDL_Handler/SDL_Handler.h"

class Visualizer {
public:
	Visualizer(SDL_Handler* handler);
	~Visualizer();

	void Update();

	void InitalizeArray();
	void Shuffle();
	void BubbleSort();
	void InsertionSort();

	int lineWidth = 5;
	int speed = 2;
	bool isSorting = false;
	int currentSortingIndex;

	const char* items[2] = { "Bubble Sort", "Insertion Sort"};
	int selected = 0;
private:
	std::vector<int> m_array;
	std::vector<size_t> m_callbackIds;
	SDL_Handler* m_handler;
	std::chrono::high_resolution_clock::time_point m_lastSortStep;

};

