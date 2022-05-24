#pragma once
#ifndef GAME_MAP_H
#define GAME_MAP_H

#include"Main.h"
#include"Object.h"
#include<vector>
#include<fstream>

#define TILE_SIZE 50
#define MAP_SIZE_X 3600
#define MAP_SIZE_Y 600
#define BG_PATH "Chapter1\\BG.jpg"
#define MAP_VALUE_PATH "Chapter1\\map.dat"
#define SAVE_POINT_PATH "Chapter1\\savepoint.txt"
#define NUMBER_SAVE_POINT 3
#define NUMBER_TELEPORT 2
#define TELE_PATH "Chapter1\\tele.txt"
#define INTRUCE "Image\\Intruce.png"
#define SPRITE_WIDTH 50
#define SPRITE_HEIGHT 72
#define SAVE_POINT_WIDTH 50
#define SAVE_POINT_HEIGHT 72
#define TELE_WIDTH 50
#define TELE_HEIGHT 80
#define FRAME_MAX 12

const int TILE_MAX_X = MAP_SIZE_X / TILE_SIZE;
const int TILE_MAX_Y = MAP_SIZE_Y / TILE_SIZE;

class Tile {
private:
	int type = 0;
	SDL_Texture* texture;
public:
	~Tile();
	void setType(const int& type);
	int getType();
	void loadTile(SDL_Renderer* render);

};

struct SavePoint { // the struct storage position of Player when player pass the save Point
	int x, y;
	SavePoint(const int& x = 0, const int& y = 0);
};

class CheckPoint : public BaseObject {
private:
	SavePoint savePoint;
	bool isPass;	

public:
	void setPass(const bool& isPass);
	void setSavePoint(const int& x, const int& y);
	int getPosX();
	void setPosX(const int& x);
	SavePoint getSavePoint();
};

class Map {
private:
	
	SDL_Texture* backGround;
	vector<vector<Tile>> tiles;
	SDL_Rect srcrect;
	SDL_Rect rect;
	int map_x;
	vector<CheckPoint> checkPoint;

public: 
	Map();
	~Map();
	void loadMap(SDL_Renderer* render);
	void showMap(SDL_Renderer* render);
	Tile getATile(int x, int y);
	void setMapX(int& map_x);
	int getMapX();
	void setMap();
	void setCheckPoint(SDL_Renderer* render, const char* path);
	SavePoint getSavePoint(const int &x, const int&y);
};

class TeleGate : public BaseObject {
private:
	int x_pos_1, x_pos_2, y_pos_1, y_pos_2;
	SDL_Rect rect1;
	SDL_Rect rect2;
	SDL_Rect frame_rect[12];
	int frame;

public:
	TeleGate();
	~TeleGate() {};
	void setRect(Map &map);
	void setFrame();
	void setPos(const int& x1, const int& y1, const int& x2, const int& y2);
	void showGate(SDL_Renderer* render, Map& map);
	int getPosX1();
	int getPosX2();
	int getPosY1();
	int getPosY2();
	bool isTele(SDL_Event& event, SDL_Renderer* render);

};

#endif // !GAMEMAP_H