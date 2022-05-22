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

SavePoint::SavePoint(const int& x, const int& y) {
	this->x = x;
	this->y = y;
}

void CheckPoint::setPass(const bool& isPass) {
	this->isPass = isPass;
}

void CheckPoint::setSavePoint(const int& x, const int& y) {
	savePoint.x = x;
	savePoint.y = y;
	rect.x = x;
	rect.y = y;
	rect.w = SAVE_POINT_WIDTH;
	rect.h = SAVE_POINT_HEIGHT;
}

SavePoint CheckPoint::getSavePoint() {
	return savePoint;
}

int CheckPoint::getPosX() {
	return savePoint.x;
}

void CheckPoint::setPosX(const int& x) {
	rect.x = x;
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
	checkPoint.resize(NUMBER_SAVE_POINT);
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
		}
	}
}

void Map::showMap(SDL_Renderer* render) {
	SDL_RenderCopy(render, backGround, &srcrect, NULL);
	for (int i = 0; i < NUMBER_SAVE_POINT; i++) {
		checkPoint[i].setPosX(checkPoint[i].getPosX() - map_x);
		checkPoint[i].show(render);
	}
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

void Map::setCheckPoint(SDL_Renderer* render, const char* path) {
	ifstream file(path);
	string img_path;
	file >> img_path;
	
	for (int i = 0; i < NUMBER_SAVE_POINT; i++) {
		int x, y;
		file >> x >> y;
		checkPoint[i].loadImage(render, img_path.c_str());
		checkPoint[i].setSavePoint(x, y);
	}
}

SavePoint Map::getSavePoint(const int& x, const int& y) {
	int x1 = x, x2 = x + SPRITE_WIDTH;
	int y1 = y, y2 = y + SPRITE_HEIGHT;

	for (int i = 0; i < NUMBER_SAVE_POINT; i++) {

		
		// check x horizon
		bool checkx1 = (x1 >= checkPoint[i].getSavePoint().x && x1 <= checkPoint[i].getSavePoint().x + SAVE_POINT_WIDTH);
		bool checkx2 = (x2 >= checkPoint[i].getSavePoint().x && x2 <= checkPoint[i].getSavePoint().x + SAVE_POINT_WIDTH);

		//check y horizon
		bool checky1 = (y1 >= checkPoint[i].getSavePoint().y && y1 <= checkPoint[i].getSavePoint().y + SAVE_POINT_HEIGHT);
		bool checky2 = (y2 >= checkPoint[i].getSavePoint().y && y2 <= checkPoint[i].getSavePoint().y + SAVE_POINT_HEIGHT);

		if (checkx1 && checky1 || checkx1 && checky2 || checkx2 && checky1 || checkx2 && checky2) {
			checkPoint[i].setPass(true);
			return checkPoint[i].getSavePoint();
		}
	}

	return SavePoint(0,0);
}

TeleGate::TeleGate() {
	texture = NULL;
	x_pos_1 = 0;
	x_pos_2 = 0;
	y_pos_1 = 0;
	y_pos_2 = 0;
	frame = 0;
}

void TeleGate::setPos(const int& x1, const int& y1, const int& x2, const int& y2) {
	x_pos_1 = x1;
	x_pos_2 = x2;
	y_pos_1 = y1;
	y_pos_2 = y2;
}

void TeleGate::setFrame() {
	for (int i = 0; i < FRAME_MAX; i++) {
		frame_rect[i].x = i * TELE_WIDTH;
		frame_rect[i].y = 0;
		frame_rect[i].w = TELE_WIDTH;
		frame_rect[i].h = TELE_HEIGHT;
	}
}

void TeleGate::setRect(Map& map) {
	rect1.x = x_pos_1 - map.getMapX();
	rect1.y = y_pos_1;
	rect1.w = TELE_WIDTH;
	rect1.h = TELE_HEIGHT;

	rect2.x = x_pos_2 - map.getMapX();
	rect2.y = y_pos_2;
	rect2.w = TELE_WIDTH;
	rect2.h = TELE_HEIGHT;
}

void TeleGate::showGate(SDL_Renderer* render, Map& map) {
	setRect(map);
	setFrame();
	frame++;
	if (frame == FRAME_MAX) frame = 0;
	SDL_RenderCopy(render, texture, &frame_rect[frame], &rect1);
	SDL_RenderCopy(render, texture, &frame_rect[frame], &rect2);
}

int TeleGate::getPosX1() {
	return x_pos_1;
}

int TeleGate::getPosY1() {
	return y_pos_1;
}

int TeleGate::getPosX2() {
	return x_pos_2;
}

int TeleGate::getPosY2() {
	return y_pos_2;
}

bool TeleGate::isTele(SDL_Event& event, SDL_Renderer* render) {
	
	BaseObject text;
	text.loadImage(render, INTRUCE);
	text.setRect(474, 550, 252, 37);
	text.show(render);
	
	return true;
}