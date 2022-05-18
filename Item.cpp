#include"Item.h"

CollectItem::CollectItem() {
	isCollected = false;
	nTexture = NULL;
	nRect.x = 0;
	nRect.y = 0;
	nRect.h = 0;
	nRect.w = 0;
	x = 0;
	y = 0;
}

void CollectItem::loadItem(SDL_Renderer* render, const char* path1, const char* path2) {
	loadImage(render, path1);
	nTexture = IMG_LoadTexture(render, path2);
	if (nTexture == NULL) {
		cout << "Cann't load Image from " << path2 << SDL_GetError() << endl;
		return;
	}
}

void CollectItem::setPos(const int& x, const int& y) {
	this->x = x;
	this->y = y;
}

void CollectItem::showItem(SDL_Renderer* render, Map &map) {
	if (!isCollected) {
		setRect(x - map.getMapX(), y, ITEM_WIDTH, ITEM_HEIGHT);
		show(render);
		SDL_RenderCopy(render, nTexture, NULL, &nRect);
	}
	else {
		SDL_RenderCopy(render, texture, NULL, &nRect);
	}
}

void CollectItem::setCollected(const bool& isCollected) {
	this->isCollected = isCollected;
}

void CollectItem::setNRect(const int& x, const int& y,const int& w,const int& h) {
	nRect.x = x;
	nRect.y = y;
	nRect.w = w;
	nRect.h = h;
}

int CollectItem::getPosX() {
	return x;
}

int CollectItem::getPosY() {
	return y;
}

SavePoint::SavePoint(const int& x, const int& y) {
	this->x = x;
	this->y = y;
}

void CheckPoint::setSavePoint(const int& x, const int& y) {
	savePoint.x = x;
	savePoint.y = y;
}

SavePoint CheckPoint::getSavePoint() {
	return savePoint;
}