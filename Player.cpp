#include"Player.h"

Player::Player() {

	 idle_right = NULL;
	 run_right = NULL;
	 jump_right = NULL;
	 fall_right = NULL;
	 idle_left = NULL;
	 run_left = NULL;
	 jump_left = NULL;
	 fall_left = NULL;

	for (int i = 0; i < MAX_FRAME_IDLE; i++) {
		idle_rect[i].x = SPRITE_WIDTH * i;
		idle_rect[i].y = 0;
		idle_rect[i].w = SPRITE_WIDTH;
		idle_rect[i].h = SPRITE_HEIGHT;
	}
	for (int i = 0; i < MAX_FRAME_OTHER; i++) {
		other_rect[i].x = SPRITE_WIDTH * i;
		other_rect[i].y = 0;
		other_rect[i].w = SPRITE_WIDTH;
		other_rect[i].h = SPRITE_HEIGHT;
	}

	frame = 0;
	x_val = 0;
	y_val = 0;
	x_pos = 0;
	y_pos = 0;
	status.direction = true;
	onGround = true;
	map_x = 0;
	special_input = false;
	
}

Player::~Player() {

}

void Player::loadImage(SDL_Renderer* render) {
	idle_right = IMG_LoadTexture(render, IDLE_RIGHT_PATH);
	idle_left = IMG_LoadTexture(render, IDLE_LEFT_PATH);
	run_right = IMG_LoadTexture(render, RUN_RIGHT_PATH);
	run_left = IMG_LoadTexture(render, RUN_LEFT_PATH);
	jump_right = IMG_LoadTexture(render, JUMP_RIGHT_PATH);
	jump_left = IMG_LoadTexture(render, JUMP_LEFT_PATH);
	fall_right = IMG_LoadTexture(render, FALL_RIGHT_PATH);
	fall_left = IMG_LoadTexture(render, FALL_LEFT_PATH);
}

void Player::inputAction(SDL_Event& event, SDL_Renderer* render) {
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
		case SDLK_w:
			status.jump = 1;
			status.idle = 0;
			break;
		case SDLK_a :
			status.direction = false;
			status.run = 1;
			status.idle = 0;
			break;
		case SDLK_d :
			status.direction = true;
			status.run = 1;
			status.idle = 0;
			break;
		case SDLK_y:
			special_input = true;
			break;
		}
	}
	else if (event.type == SDL_KEYUP) {
		switch (event.key.keysym.sym) {
		case SDLK_w:
			y_val = 0;
			status.jump = 0;
			status.idle = 1;
			break;
		case SDLK_a:
			x_val = 0;
			status.run = 0;
			status.idle = 1;
			break;
		case SDLK_d:
			x_val = 0;
			status.run = 0;
			status.idle = 1;
			break;
		case SDLK_y:
			special_input = false;
			break;
		}
		
		frame = 0;
	}
	
}

void Player::show(SDL_Renderer* render) {
	rect.y = y_pos;
	rect.x = x_pos - map_x;
	if (status.direction) {  // horizon is right

		if (status.jump) {
			if (frame >= MAX_FRAME_OTHER) frame = 0;
			SDL_RenderCopy(render, jump_right, &other_rect[frame], &rect);
			frame++;
		}
		
		else if (status.run) {
			if (frame >= MAX_FRAME_OTHER) frame = 0;
			Mix_PlayChannel(-1, RUN, 0);
			SDL_RenderCopy(render, run_right, &other_rect[frame], &rect);
			frame++;
		}
		else if (status.idle) {
			if (frame >= MAX_FRAME_IDLE) frame = 0;
			SDL_RenderCopy(render, idle_right, &idle_rect[frame], &rect);
			frame++;
		}	
	}

	else { // horizon is left
		if (status.jump) {
			if (frame >= MAX_FRAME_OTHER) frame = 0;
			SDL_RenderCopy(render, jump_left, &other_rect[frame], &rect);
			frame++;
		}
		else if (status.run) {
			if (frame >= MAX_FRAME_OTHER) frame = 0;
			Mix_PlayChannel(-1, RUN, 0);
			SDL_RenderCopy(render, run_left, &other_rect[frame], &rect);
			frame++;
		}
		else if (status.idle) {
			if (frame >= MAX_FRAME_IDLE) frame = 0;
			SDL_RenderCopy(render, idle_left, &idle_rect[frame], &rect);
			frame++;
		}
	}
}

void Player::check_map(Map& map) {
	int x1, x2, y1, y2;
	int height_min = SPRITE_HEIGHT < TILE_SIZE ? SPRITE_HEIGHT : TILE_SIZE;
	x1 = (x_pos + x_val) / TILE_SIZE;
	x2 = (x_pos + x_val + SPRITE_WIDTH - 1) / TILE_SIZE;
	y1 = (y_pos) / TILE_SIZE;
	y2 = (y_pos + height_min - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < TILE_MAX_X && y1 >= 0 && y2 < TILE_MAX_Y) {
		if (x_val > 0) {
			Tile tile1 = map.getATile(y1, x2);
			Tile tile2 = map.getATile(y2, x2);
			if (tile1.getType() != 0 || tile2.getType() != 0) {
				x_pos = x2 * TILE_SIZE - x_val + 1 - SPRITE_WIDTH;
				x_val = 0;
			}
		}

		if (x_val < 0) {
			Tile tile1 = map.getATile(y1, x1);
			Tile tile2 = map.getATile(y2, x1);
			if (tile1.getType() != 0 || tile2.getType() != 0) {
				x_pos = (x1 + 1)* TILE_SIZE;
				x_val = 0;
			}
		}
	}

	int width_min = SPRITE_WIDTH < TILE_SIZE ? SPRITE_WIDTH : TILE_SIZE;
	x1 = (x_pos) / TILE_SIZE;
	x2 = (x_pos + width_min - 1) / TILE_SIZE;
	y1 = (y_pos + y_val) / TILE_SIZE;
	y2 = (y_pos + y_val + SPRITE_HEIGHT - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < TILE_MAX_X && y1 >= 0 && y2 < TILE_MAX_Y) {
		if (y_val < 0) {
			Tile tile1 = map.getATile(y1, x1);
			Tile tile2 = map.getATile(y1, x2);
			if (tile1.getType() != 0 || tile2.getType() != 0) {
				y_pos = (y1 + 1) * TILE_SIZE;
				y_val = 0;
			}
			
		}

		if (y_val > 0) {
			Tile tile1 = map.getATile(y2, x1);
			Tile tile2 = map.getATile(y2, x2);
			if (tile1.getType() != 0 || tile2.getType() != 0) {
				y_pos = y2 * TILE_SIZE - SPRITE_HEIGHT;
				y_val = 0;
				onGround = true;
			}
		}
		
	}
	
	if (x_pos + x_val >= 0 && x_pos + x_val + SPRITE_WIDTH <= MAP_SIZE_X) x_pos += x_val;
	if (y_pos + y_val >= 0 && y_pos <= MAP_SIZE_Y) y_pos += y_val;
	if (y_pos >= MAP_SIZE_Y) returnSavePoint();
}

void Player::move(Map& map, vector<CollectItem>& keyItem, vector<CollectItem>& subItem) {
	
	x_val = 0;
	y_val += 5;
	if (y_val > MAX_FALL) y_val = MAX_FALL;

	if (status.run) {
		if (status.direction) x_val = MOVE_STEP;
		else x_val = -MOVE_STEP;
	}

	if (status.jump) {
		if (onGround) {
			y_val = -JUMP_STEP;
			onGround = false;
		}
	}
	check_map(map);
	check_item(keyItem, subItem);
	check_SavePoint(map);
	centerMap(map);
	
}

void Player::check_item(vector<CollectItem>& keyItem, vector<CollectItem>& subItem) {

	int x1 = x_pos, x2 = x_pos + SPRITE_WIDTH;
	int y1 = y_pos, y2 = y_pos + SPRITE_HEIGHT;

	// check key item
	for (int i = 0; i < NUMBER_KEY_ITEM; i++) {
		if (keyItem[i].collected()) continue;
		
		// check x horizon
		bool checkx1 = (x1 >= keyItem[i].getPosX() && x1 <= keyItem[i].getPosX() + ITEM_WIDTH);
		bool checkx2 = (x2 >= keyItem[i].getPosX() && x2 <= keyItem[i].getPosX() + ITEM_WIDTH);
		
		//check y horizon
		bool checky1 = (y1 >= keyItem[i].getPosY() && y1 <= keyItem[i].getPosY() + ITEM_HEIGHT);
		bool checky2 = (y2 >= keyItem[i].getPosY() && y2 <= keyItem[i].getPosY() + ITEM_HEIGHT);

		if (checkx1 && checky1 || checkx1 && checky2 || checkx2 && checky1 || checkx2 && checky2) {
			keyItem[i].setCollected(true);
			Mix_PlayChannel(-1, COLLECT, 0);
		}
	}

	// check sub item
	for (int i = 0; i < NUMBER_KEY_ITEM; i++) {
		if (subItem[i].collected()) continue;

		// check x horizon
		bool checkx1 = (x1 >= subItem[i].getPosX() && x1 <= subItem[i].getPosX() + ITEM_WIDTH);
		bool checkx2 = (x2 >= subItem[i].getPosX() && x2 <= subItem[i].getPosX() + ITEM_WIDTH);

		//check y horizon
		bool checky1 = (y1 >= subItem[i].getPosY() && y1 <= subItem[i].getPosY() + ITEM_HEIGHT);
		bool checky2 = (y2 >= subItem[i].getPosY() && y2 <= subItem[i].getPosY() + ITEM_HEIGHT);

		if (checkx1 && checky1 || checkx1 && checky2 || checkx2 && checky1 || checkx2 && checky2) {
			subItem[i].setCollected(true);
			Mix_PlayChannel(-1, COLLECT, 0);
		}
	}
}

void Player::check_SavePoint(Map& map) {
	if (map.getSavePoint(x_pos, y_pos).x != 0 && map.getSavePoint(x_pos, y_pos).y != 0) 
		savePoint = map.getSavePoint(x_pos, y_pos);
}

void Player::centerMap(Map& map) {
	map_x = x_pos - SCREEN_WIDTH / 2;
	if (map_x < 0)
	{
		map_x = 0;
	}

	else if (map_x + SCREEN_WIDTH >= MAP_SIZE_X)
	{
		map_x = MAP_SIZE_X - SCREEN_WIDTH;
	}
	
	map.setMapX(map_x);
	map.setMap();
}

void Player::returnSavePoint() {
	x_pos = savePoint.x;
	y_pos = savePoint.y;
}

void Player::teleport(vector<TeleGate>& teleGate, SDL_Event& event, SDL_Renderer* render) {
	for (int i = 0; i < NUMBER_TELEPORT; i++) {
		int gate_posX1 = teleGate[i].getPosX1();
		int gate_posX2 = teleGate[i].getPosX2();
		int gate_posY1 = teleGate[i].getPosY1();
		int gate_posY2 = teleGate[i].getPosY2();

		int x_center = x_pos + SPRITE_WIDTH / 2;
		int y_center = y_pos + SPRITE_HEIGHT / 2;

		bool checkX = (x_center >= gate_posX1 && x_pos <= gate_posX1 + TELE_WIDTH);
		bool checkY = (y_center >= gate_posY1 && y_pos <= gate_posY1 + TELE_HEIGHT);
		if (checkX && checkY) {
			if (teleGate[i].isTele(event, render) && special_input) {
				special_input = false;
				x_pos = gate_posX2;
				y_pos = gate_posY2;
			}
		}
		
		checkX = (x_center >= gate_posX2 && x_pos <= gate_posX2 + TELE_WIDTH);
		checkY = (y_center >= gate_posY2 && y_pos <= gate_posY2 + TELE_HEIGHT);
		if (checkX && checkY) {
			if (teleGate[i].isTele(event, render) && special_input) {
				special_input = false;
				x_pos = gate_posX1;
				y_pos = gate_posY1;
			}
		}
	}
}

Position Player::getPos() {
	return Position(x_pos, y_pos);
}