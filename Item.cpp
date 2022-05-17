#include"Item.h"

void Item::setTypeItem(int& typeItem) {
	this->typeItem = typeItem;
}

void Item::showItem(SDL_Renderer* render) {
	setRect(x, y, ITEM_WIDTH, ITEM_HEIGHT);
}