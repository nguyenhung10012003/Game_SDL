#include"Game_Control.h"

Menu::Menu() {
    background = NULL;
    gameStart = false;
}

Menu::~Menu() {

}

void Menu::loadBG(SDL_Renderer* render, const char* path) {
    background = IMG_LoadTexture(render, path);
    if (background == NULL) {
        cout << "Can't load IMG" << endl;
        return;
    }
}

bool Menu::getGameStart() {
    return gameStart;
}

void Menu::menuLoop(SDL_Renderer* render) {
    
    SDL_Event event;
    UINT32 frameStart, frameTime;
    bool isRunning = true;
    int mouse_x, mouse_y;

    while (!gameStart && isRunning) {
        frameStart = SDL_GetTicks();
        SDL_RenderClear(render);
        
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                switch (event.button.button) {
                case SDL_BUTTON_LEFT:
                    if (mouse_x >= GAME_START_X1 && mouse_x <= GAME_START_X2
                        && mouse_y >= GAME_START_Y1 && mouse_y <= GAME_START_Y2) 
                        gameStart = true;
                }
                break;
            case SDL_MOUSEMOTION:
                mouse_x = event.motion.x;
                mouse_y = event.motion.y;
                //cout << x << " " << y << endl;
                break;
         
            }
        }

        SDL_RenderCopy(render, background, NULL, NULL);
        SDL_RenderPresent(render);
        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < DELAY_TIME)
        {
            SDL_Delay(DELAY_TIME - frameTime);
        }

    }
}

void gameLoop(SDL_Renderer* render) {
    Map map;
    map.loadMap(render);

    Player player;
    player.loadImage(render);
    player.setRect(0, 300, SPRITE_WIDTH, SPRITE_HEIGHT);

    bool isRunning = true;
    SDL_Event event;
    UINT32 frameStart, frameTime;

    while (isRunning) {

        frameStart = SDL_GetTicks();
        SDL_RenderClear(render);
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                isRunning = false;
                break;
            default:
                break;
            }
            player.inputAction(event, render);
        }

        player.move(map);
        map.showMap(render);
        player.show(render);
        SDL_RenderPresent(render);

        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < DELAY_TIME)
        {
            SDL_Delay(DELAY_TIME - frameTime);
        }
    }
}