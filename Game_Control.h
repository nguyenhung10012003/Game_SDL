#ifndef GAME_CONTROL_H
#define GAME_CONTROL_H

#include"Player.h"
#include"Collapse.h"
#include<vector>

#define MENU_BG_PATH "Menu\\BG.png"
#define PAUSE_PATH "Chapter1\\pause.png"
#define GAME_START_X1 430
#define GAME_START_Y1 280
#define GAME_START_X2 770
#define GAME_START_Y2 320
#define QUIT_X1 556
#define QUIT_Y1 365
#define QUIT_X2 643
#define QUIT_Y2 386
#define WON_PATH "Chapter1\\won.PNG"
#define LOSE_PATH "Chapter1\\lose.PNG"
#define FINISH_PATH "Chapter1\\finish.txt"

class Menu {
private:
	SDL_Texture* background;
	bool gameStart = false;

public:
	Menu();
	~Menu();
	void loadBG(SDL_Renderer* render, const char* path);
	void menuLoop(SDL_Renderer* render);
	bool getGameStart();
};

void loadAllItem(vector<CollectItem>& keyItem, vector<CollectItem>& subItem, SDL_Renderer* render);
void loadFinish(SDL_Renderer* render, TeleGate& finishGate);
void gameLoop(SDL_Renderer* render, bool& won);
void gameOver(Player& player, Collapse& collapse, bool& isRunning, bool& won);
void Won(Player& player, TeleGate& finishGate, bool& isRunning, bool& won);
void endGame(SDL_Renderer* render, const bool& won);

#endif // !GAME