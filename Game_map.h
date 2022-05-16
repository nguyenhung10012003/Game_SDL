#pragma once
#ifndef GAME_MAP_H
#define GAME_MAP_H

#include"Main.h"
#include<vector>
#include<fstream>

#define TILE_SIZE 50
#define MAP_SIZE_X 3600
#define MAP_SIZE_Y 600
#define BG_PATH "Chapter1\\BG.jpg"
#define MAP_VALUE_PATH "Chapter1\\map.dat"

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

class Map {
private:
	
	SDL_Texture* backGround;
	vector<vector<Tile>> tiles;
	SDL_Rect srcrect;
	SDL_Rect rect;
	int map_x;

public: 
	Map();
	~Map();
	void loadMap(SDL_Renderer* render);
	void showMap(SDL_Renderer* render);
	Tile getATile(int x, int y);
	void setMapX(int& map_x);
	int getMapX();
	void setMap();
};

#endif // !GAMEMAP_H