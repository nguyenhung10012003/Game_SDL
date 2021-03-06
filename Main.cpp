#include <iostream>
#include"Game_Control.h"

int main()
{
    startSDL();
    SDL_Window* window = creatWindow();
    SDL_Renderer* render = creatRenderer(window);
    

    Menu menu;
    menu.loadBG(render, MENU_BG_PATH);
    
    menu.menuLoop(render);
    bool won = false;
    if (menu.getGameStart()) gameLoop(render, won);
    if (menu.getGameStart()) endGame(render, won);
    
    

    SDL_Quit();
    return 0;
}