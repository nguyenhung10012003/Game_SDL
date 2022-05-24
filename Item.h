#pragma once
#ifndef ITEM_H
#define ITEM_H

#include"Main.h"
#include"Object.h"
#include"Game_map.h"

#define NUMBER_KEY_ITEM 5
#define NUMBER_SUB_ITEM 5
#define NUMBER_TELEPORT 2
#define ITEM_WIDTH 50
#define ITEM_HEIGHT 50
#define ITEM_PATH "Chapter1\\Item.txt"
#define HEAD_PATH "Item\\"

class CollectItem : public BaseObject{
private:
	SDL_Rect nRect;
	bool isCollected;
	SDL_Texture* nTexture;
	int x, y;

public:
	CollectItem();
	void loadItem(SDL_Renderer* render, const char* path1, const char* path2);
	void setPos(const int& x, const int& y);
	void showItem(SDL_Renderer* render, Map &map);
	void setCollected(const bool& isCollected);
	void setNRect(const int& x, const int& y, const int& w, const int& h);
	int getPosX();
	int getPosY();
	bool collected();
};



#endif // !ITEM_H