#pragma once
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
#include <thread>
#include <chrono>


#include "SDL_Handler/SDL_Handler.h"
#include "SDL_Handler/SDLBeeper.h"


enum class OperationType {
	COMPARE,
	SWAP
};

struct Operation {
	OperationType type;
	int indexA;
	int indexB;
};

class Visualizer {
public:
	Visualizer(SDL_Handler* handler);
	~Visualizer();

	void Update();

	void RenderLines();

	void InitalizeArray();
	void Shuffle();
	void BubbleSort();
	void InsertionSort();

	void StartSort();
	void Resume();
	void StopSort();

	void ResetOperations();

	void playSwap(int index);

	int lineWidth = 5;
	int delay = 2;
	bool isSorting = false;
	int currentSortingIndex;

	const char* algos[2] = {"Bubble Sort", "Insertion Sort"};
	int selected = 0;
	
private:
	std::vector<int> m_array;
	std::vector<size_t> m_callbackIds;
	std::vector<Operation> m_operations;
	int m_currentOperationIndex;
	SDL_Handler* m_handler;
	std::chrono::high_resolution_clock::time_point m_lastOperationTime;
	SDLBeeper beeper;

};

