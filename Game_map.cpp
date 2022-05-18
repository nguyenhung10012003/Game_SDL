#include"Game_map.h"
#include<string>


Tile::~Tile() {}

void Tile::setType(const int& type) {
	this->type = type;
}

int Tile::getType() {
	return type;
}

void Tile::loadTile(SDL_Renderer* render) {
	if (type == 0) return;
	string path = "Chapter1\\Tile\\" + to_string(type) + ".png";
	texture = IMG_LoadTexture(render,path.c_str());
	if (texture == NULL) {
		cout << "Can not load Tile" << endl;
		return;
	}
}

Map::Map() {
	rect.x = 0;
	rect.y = 0;
	rect.w = 0;
	rect.h = 0;
	map_x = 0;
	backGround = NULL;
	srcrect.x = 0;
	srcrect.y = 0;
	srcrect.w = SCREEN_WIDTH;
	srcrect.h = SCREEN_HEIGHT;
	
}

Map::~Map() {
	SDL_DestroyTexture(backGround);
}

void Map::loadMap(SDL_Renderer* render) {
	this->backGround = IMG_LoadTexture(render, BG_PATH);
	
	ifstream input_file(MAP_VALUE_PATH);
	if (!input_file) return;
	
	tiles.resize(TILE_MAX_Y);

	for (int i = 0; i < TILE_MAX_Y; i++) {

		tiles[i].resize(TILE_MAX_X);

		for (int j = 0; j < TILE_MAX_X; j++) {
			int type;
			input_file >> type;
			tiles[i][j].setType(type);
			//tiles[i][j].loadTile(render);
		}
	}
}

void Map::showMap(SDL_Renderer* render) {
	SDL_RenderCopy(render, backGround, &srcrect, NULL);
	/*for (int i = 0; i < TILE_MAX_Y; i++) {
		for (int j = 0; j < TILE_MAX_X; j++) {
			if (tiles[i][j].getType() == 0) continue;
			tiles[i][j].setRect(j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE);
			tiles[i][j].show(render);
		}
	}*/
}

Tile Map::getATile(int x, int y) {
	return tiles[x][y];
}

void Map::setMapX(int& map_x) {
	this->map_x = map_x;
}

int Map::getMapX() {
	return map_x;
}

void Map::setMap() {
	srcrect.x = map_x;
	srcrect.y = 0;
}