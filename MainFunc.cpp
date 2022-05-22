#include"Main.h"

void startSDL() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return;
    }

    if (TTF_Init() < 0)
    {
        SDL_Log("%s", TTF_GetError());
        return;
    }

    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) return;
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