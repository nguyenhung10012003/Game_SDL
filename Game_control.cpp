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
    int mouse_x = 0, mouse_y = 0;

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

void loadAllItem(vector<CollectItem> &keyItem, vector<CollectItem>& subItem, SDL_Renderer* render) {
    fstream file(ITEM_PATH);

    // load all key item
    for (int i = 0; i < NUMBER_KEY_ITEM; i++) {
        string path1 = "", path2 = "";
        int x, y;
        
        file >> path1 >> path2 >> x >> y;
        keyItem[i].loadItem(render, (HEAD_PATH + path1).c_str(), (HEAD_PATH + path2).c_str());
        int ny = 0, nx = SCREEN_WIDTH - (i + 1) * ITEM_WIDTH;
        keyItem[i].setPos(x, y);
        keyItem[i].setNRect(nx, ny, ITEM_WIDTH, ITEM_HEIGHT);
    }
    // load done !

    // load sub item
    string path = "";
    file >> path;
    for (int i = 0; i < NUMBER_SUB_ITEM; i++) {
        int x, y;
        file >> x >> y;
        subItem[i].loadItem(render, (HEAD_PATH + path).c_str(), (HEAD_PATH + path).c_str());
        subItem[i].setNRect(0, 0, ITEM_WIDTH, ITEM_HEIGHT);
    }
    // load done !
    cout << "done";
}

void showAllItem(vector<CollectItem>& keyItem, vector<CollectItem>& subItem, SDL_Renderer* render, Map &map) {
    for (int i = 0; i < NUMBER_KEY_ITEM; i++) 
        keyItem[i].showItem(render, map);

    for (int i = 0; i < NUMBER_SUB_ITEM; i++) 
        subItem[i].showItem(render, map);
    
}

void gameLoop(SDL_Renderer* render) {
    Map map;
    map.loadMap(render);

    Player player;
    player.loadImage(render);
    player.setRect(0, 300, SPRITE_WIDTH, SPRITE_HEIGHT);
    
    vector<CollectItem> keyItem(NUMBER_KEY_ITEM);
    vector<CollectItem> subItem(NUMBER_SUB_ITEM);
    loadAllItem(keyItem, subItem, render);

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
        showAllItem(keyItem,subItem,render, map);
        player.show(render);
        SDL_RenderPresent(render);

        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < DELAY_TIME)
        {
            SDL_Delay(DELAY_TIME - frameTime);
        }
    }
}