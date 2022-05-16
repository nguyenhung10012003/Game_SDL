#pragma once

#ifndef OBJECT_H
#define OBJECT_H

#include"Main.h"
#include"Game_map.h"


#define MAX_FRAME_IDLE 10
#define MAX_FRAME_OTHER 8
#define SPRITE_WIDTH 50
#define SPRITE_HEIGHT 72
#define IDLE_RIGHT_PATH "Chapter1\\Main\\Idle_right.png"
#define JUMP_RIGHT_PATH	"Chapter1\\Main\\Jump_Right.png"
#define RUN_RIGHT_PATH "Chapter1\\Main\\1.png"
#define FALL_RIGHT_PATH "Chapter1\\Main\\Fall_Right.png"
#define IDLE_LEFT_PATH "Chapter1\\Main\\Idle_Left.png"
#define JUMP_LEFT_PATH "Chapter1\\Main\\Jump_Left.png"
#define RUN_LEFT_PATH "Chapter1\\Main\\2.png"
#define FALL_LEFT_PATH "Chapter1\\Main\\Fall_Left.png"

const int MOVE_STEP = 5;
const int JUMP_STEP = 15;
const int FALL_STEP = 5;
const int MAX_FALL = 20;

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
	void show(SDL_Renderer* render);
	void setRect(const int& x, const int& y, const int& w, const int& h);
};

class Player : public BaseObject {
private:
	SDL_Rect idle_rect[10], other_rect[8];
	SDL_Texture* idle_right;
	SDL_Texture* run_right;
	SDL_Texture* jump_right;
	SDL_Texture* fall_right;
	SDL_Texture* idle_left;
	SDL_Texture* run_left;
	SDL_Texture* jump_left;
	SDL_Texture* fall_left;

	int frame;
	int x_val, y_val;
	int x_pos, y_pos;
	Status status;
	bool onGround;
	int map_x;

public: 
	Player();
	~Player();
	void loadImage(SDL_Renderer* render);
	void inputAction(SDL_Event& event, SDL_Renderer* render);
	void show(SDL_Renderer* render);
	void move(Map& map);
	void check_map(Map& map);
	void freeFall(Map& map);
	void death();
	void centerOnMap(Map& map);

};

#endif