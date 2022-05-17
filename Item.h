#pragma once
#ifndef ITEM_H
#define ITEM_H

#include"Main.h"
#include"Object.h"

#define NUMBER_KEY_ITEM 5
#define NUMBER_SUB_ITEM 5
#define NUMBER_SAVE_POINT 3
#define NUMBER_TELEPORT 2
#define ITEM_WIDTH 50
#define ITEM_HEIGHT 50
#define ITEM_PATH "Chapter1\\Item\\Item.txt"

class Item : public BaseObject{
public:
	void setTypeItem(int& typeItem);
	void showItem(SDL_Renderer* render);
private:
	/*
	* typeItem = 0 : None item
	* typeItem = 1 : Key Item
	* typeItem = 2 : Sub Item
	* typeItem = 3 : Save Point
	* typeItem = 4 : teleport gate
	*/
	char typeItem;
	SDL_Rect srcRect; // only Key Item and Sub item use this member
	int x, y; // position of the item
};

#endif // !ITEM_H