#include"Main.h"

void startSDL() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return;
    }
}

SDL_Window* creatWindow() {
    SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE, 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        cout << "SDL_CreateWindow Error: " << SDL_GetError() << endl;
        return NULL;
    }
    return window;
}

SDL_Renderer* creatRenderer(SDL_Window* window) {
    SDL_Renderer* render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (render == nullptr) {
        cout << "SDL_CreateRenderer Error: " << SDL_GetError() << endl;
        return NULL;
    }
    return render;
}