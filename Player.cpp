#include"Object.h"

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
			//y_val = -JUMP_STEP;
			status.jump = 1;
			status.idle = 0;
			break;
		case SDLK_a :
			//x_val = -MOVE_STEP;
			status.direction = false;
			status.run = 1;
			status.idle = 0;
			break;
		case SDLK_d :
			//x_val = MOVE_STEP;
			status.direction = true;
			status.run = 1;
			status.idle = 0;
			break;
		case SDLK_s :
			//y_val = 0;

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

	cout << x1 << " " << x2 << " " << y1 << " " << y2 << " " << x_pos << " " << y_pos << endl; // 1 2 6 7 

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
			}
		}
		onGround = true;
	}
	
	if (x_pos + x_val >= 0 && x_pos + x_val + SPRITE_WIDTH <= MAP_SIZE_X) x_pos += x_val;
	if (y_pos + y_val >= 0 && y_pos + y_val + SPRITE_HEIGHT <= MAP_SIZE_Y) y_pos += y_val;
	
}

void Player::move(Map& map) {
	
	x_val = 0;
	y_val += 5;
	if (y_val > MAX_FALL) y_val = MAX_FALL;

	if (status.run) {
		if (status.direction) x_val = MOVE_STEP;
		else x_val = -MOVE_STEP;
	}

	if (status.jump && onGround) {
		y_val = -JUMP_STEP;
		onGround = false;
	}
	check_map(map);
	centerOnMap(map);
	death();
}

void Player::centerOnMap(Map& map) {
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
	cout << map_x << endl;
}

void Player::freeFall(Map &map) {
	while (map.getATile(y_pos + SPRITE_HEIGHT, x_pos).getType() == 0) {
		if (y_pos + 4 <= SCREEN_HEIGHT) y_pos += 4;
	}
}

void Player::death() {
	if (y_pos >= MAP_SIZE_Y - SPRITE_HEIGHT) {
		cout << "is death";
	}
}