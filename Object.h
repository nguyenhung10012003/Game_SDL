#pragma once

#ifndef OBJECT_H
#define OBJECT_H

#include"Main.h"

struct Position {
	int x;
	int y;
	Position(const int& x = 0, const int& y = 0) {
		this->x = x;
		this->y = y;
	}
};

struct Status {
	bool idle = 1, run = 0, jump = 0; 
	
	bool direction = true;
	// direction = true: sprite direct right
	// direction = false: sprite derect left
};

class BaseObject {
protected:
	SDL_Rect rect;
	SDL_Texture* texture;

public:
	BaseObject();
	~BaseObject();
	virtual void loadImage(SDL_Renderer* render, const char* file);
	virtual void show(SDL_Renderer* render);
	void setRect(const int& x, const int& y, const int& w, const int& h);
};

#endif