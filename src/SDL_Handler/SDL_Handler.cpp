#include "SDL_Handler.h"


SDL_Handler::SDL_Handler() {
    Initalize();
}

SDL_Handler::~SDL_Handler() {
    Destroy();
}

bool SDL_Handler::Initalize() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "Failed to initialize the SDL2 library\n";
        return false;
    }

    window = SDL_CreateWindow(
        "SDL2 TESTING",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1280, 720,
        SDL_WINDOW_RESIZABLE
    );

    if (!window)
    {
        std::cout << "Failed to create window\n";
        return -1;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);


    // get window dimensions
    int windowWidth = GetWindowWidth();
    int windowHeight = GetWindowHeight();

    // print dimensions
    std::cout << "Window dimensions: " << windowWidth << "x" << windowHeight << std::endl;

    return true;
}



void SDL_Handler::Destroy() {

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

int SDL_Handler::GetWindowHeight() {
    return SDL_GetWindowSurface(window)->h;
}

int SDL_Handler::GetWindowWidth() {
    return SDL_GetWindowSurface(window)->w;
}

void SDL_Handler::PollEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        // Handle events here
        switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        }

        if (m_eventCallbacks.count(static_cast<SDL_EventType>(event.type)) > 0) {
            for (auto& callback : m_eventCallbacks[static_cast<SDL_EventType>(event.type)]) {
                callback(event);
            }
        }
    }
}
size_t SDL_Handler::RegisterCallBack(SDL_EventType eventType, std::function<void(SDL_Event&)> callback) {
    m_eventCallbacks[eventType].push_back(callback);
    size_t callbackId = m_nextCallbackId++;
    m_callbackIds[callbackId] = { eventType, m_eventCallbacks[eventType].size() - 1 };
    return callbackId;
}

void SDL_Handler::UnregisterCallback(size_t callbackId) {
    if (m_callbackIds.count(callbackId) > 0) {
        SDL_EventType eventType = m_callbackIds[callbackId].first;
        size_t index = m_callbackIds[callbackId].second;
        if (index < m_eventCallbacks[eventType].size()) {
            m_eventCallbacks[eventType].erase(m_eventCallbacks[eventType].begin() + index);
            // Adjust the indices of all remaining callbacks for this event type
            for (auto& pair : m_callbackIds) {
                if (pair.second.first == eventType && pair.second.second > index) {
                    --pair.second.second;
                }
            }
        }
        m_callbackIds.erase(callbackId);
    }
}
