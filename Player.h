#pragma once
#ifndef PLAYER_H
#define PLAER_H

#include"Main.h"
#include"Object.h"
#include"Item.h"

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

const int MOVE_STEP = 8;
const int JUMP_STEP = 30;
const int FALL_STEP = 5;
const int MAX_FALL = 15;

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
	void move(Map& map, vector<CollectItem>& keyItem, vector<CollectItem>& subItem);
	void check_map(Map& map);
	void check_item(vector<CollectItem> &keyItem, vector<CollectItem> &subItem);
	void centerMap(Map& map);

};

#endif // !1