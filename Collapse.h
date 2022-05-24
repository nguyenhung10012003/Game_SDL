#pragma once
#ifndef COLLAPSE_H
#define COLLAPSE_H

#include"Main.h"
#include"Object.h"
#include"Game_map.h"

#define COLLAPSE_PATH "Image\\Collapse.png"
#define COLLAPSE_WIDTH 520
#define COLLAPSE_HEIGHT 1200
#define COLLAPSE_FRAME 12
#define COLLAPSE_SPEED 1

class Collapse : public BaseObject {
private:
	int x, y;
	int frame;
	SDL_Rect nRect;
	SDL_Rect frameRect[COLLAPSE_FRAME];

public:
	Collapse();
	~Collapse();
	void setFrame();
	void showObj(SDL_Renderer* render, Map& map);
	Position getPos();
	void move();
};

#endif // !COLLAPSE_H
