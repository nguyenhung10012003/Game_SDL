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
        subItem[i].setPos(x, y);
        subItem[i].setNRect(0, 0, ITEM_WIDTH, ITEM_HEIGHT);
    }
    // load done !
}

void showAllItem(vector<CollectItem>& keyItem, vector<CollectItem>& subItem, SDL_Renderer* render, Map &map) {
    for (int i = 0; i < NUMBER_KEY_ITEM; i++) 
        keyItem[i].showItem(render, map);

    for (int i = 0; i < NUMBER_SUB_ITEM; i++) 
        subItem[i].showItem(render, map);
    
}

void loadAllTele(vector<TeleGate>& telegate, SDL_Renderer* render, Map& map) {
    ifstream file(TELE_PATH);
    string img_path;
    file >> img_path;

    for (int i = 0; i < NUMBER_TELEPORT; i++) {
        int x1, y1, x2, y2;
        file >> x1 >> y1 >> x2 >> y2;
        telegate[i].loadImage(render, img_path.c_str());
        telegate[i].setPos(x1, y1, x2, y2);
    }
}

void loadFinish(SDL_Renderer* render, TeleGate& finishGate) {
    ifstream file(FINISH_PATH);
    string img_path;
    file >> img_path;
    finishGate.loadImage(render, img_path.c_str());
    int x1, y1, x2, y2;
    file >> x1 >> y1 >> x2 >> y2;
    finishGate.setPos(x1, y1, x2, y2);
}

void showAllTele(vector<TeleGate>& telegate, SDL_Renderer* render, Map& map) {
    for (int i = 0; i < NUMBER_TELEPORT; i++) telegate[i].showGate(render, map);
}

void gameLoop(SDL_Renderer* render, bool& won) {
    Map map;
    map.loadMap(render);
    map.setCheckPoint(render, SAVE_POINT_PATH);

    Player player;
    player.loadImage(render);
    player.setRect(0, 300, SPRITE_WIDTH, SPRITE_HEIGHT);
    
    vector<CollectItem> keyItem(NUMBER_KEY_ITEM);
    vector<CollectItem> subItem(NUMBER_SUB_ITEM);
    loadAllItem(keyItem, subItem, render);

    vector<TeleGate> teleGate(NUMBER_TELEPORT);
    loadAllTele(teleGate, render, map);

    TeleGate finishGate;
    loadFinish(render, finishGate);

    Collapse collapse;
    collapse.loadImage(render, COLLAPSE_PATH);
    collapse.setFrame();

    bool isRunning = true;
    SDL_Event event;
    UINT32 frameStart, frameTime;
    
    Mix_Music* BGM = Mix_LoadMUS(BGM_PATH);
    Mix_PlayMusic(BGM, -1);

    while (isRunning) {
        
        frameStart = SDL_GetTicks();
        SDL_RenderClear(render);
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                isRunning = false;
                exit(1);
                break;
            default:
                break;
            }
            player.inputAction(event, render);
        }

        player.move(map,keyItem,subItem);
        gameOver(player, collapse, isRunning, won);
        map.showMap(render);
        player.teleport(teleGate, event, render);
        showAllItem(keyItem,subItem,render, map);
        showAllTele(teleGate, render, map);
        finishGate.showGate(render, map);
        Won(player, finishGate, isRunning, won);
        player.show(render);
        collapse.showObj(render, map);
        SDL_RenderPresent(render);

        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < DELAY_TIME)
        {
            SDL_Delay(DELAY_TIME - frameTime);
        }
    }
}

void gameOver(Player& player, Collapse& collapse, bool& isRunning, bool& won) {
    Position player_pos = player.getPos();
    Position collapse_pos = collapse.getPos();

    if (player_pos.x <= collapse_pos.x + COLLAPSE_WIDTH - SPRITE_WIDTH / 2) {
        isRunning = false;
        won = false;
    }
}

void endGame(SDL_Renderer* render, const bool& won) {

    SDL_Texture* texture;
    Mix_Music* EM;

    if (won) {
        texture = IMG_LoadTexture(render, WON_PATH);
        EM = Mix_LoadMUS(WON_SOUND_PATH);
    }
    else {
        texture = IMG_LoadTexture(render, LOSE_PATH);
        EM = Mix_LoadMUS(GAMEOVER_SOUND_PATH);
    }

    bool loop = true;
    SDL_Event event;
    UINT32 frameStart, frameTime;
   
    Mix_PlayMusic(EM, 1);
    while (loop) {
        frameStart = SDL_GetTicks();
        SDL_RenderClear(render);

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                loop = false;
                break;
            case SDL_KEYDOWN: // press any key will exit
                loop = false;
                break;
            default:
                break;
            }
        }

        SDL_RenderCopy(render, texture, NULL, NULL);
        SDL_RenderPresent(render);
        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < DELAY_TIME)
        {
            SDL_Delay(DELAY_TIME - frameTime);
        }
    }
}

void Won(Player& player, TeleGate& finishGate, bool& isRunning, bool& won) {
    Position p_pos = player.getPos();
    int x_center = p_pos.x + SPRITE_WIDTH / 2 ;
    int y_center = p_pos.y + SPRITE_HEIGHT / 2 - 20;
    int gate_posX1 = finishGate.getPosX1();
    int gate_posY1 = finishGate.getPosY1();

    bool checkX = (x_center >= gate_posX1 && p_pos.x <= gate_posX1 + TELE_WIDTH);
    bool checkY = (y_center >= gate_posY1 && p_pos.y <= gate_posY1 + TELE_HEIGHT);

    if (checkX && checkY) {
        won = true;
        isRunning = false;
    }
}