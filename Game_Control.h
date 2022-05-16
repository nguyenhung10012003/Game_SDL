#ifndef GAME
#define GAME_CONTROL_H

#include"Main.h"
#include"Game_map.h"
#include"Object.h"

#define MENU_BG_PATH "Menu\\BG.png"
#define GAME_START_X1 430
#define GAME_START_Y1 280
#define GAME_START_X2 770
#define GAME_START_Y2 320

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

void gameLoop(SDL_Renderer* render);

#endif // !GAME