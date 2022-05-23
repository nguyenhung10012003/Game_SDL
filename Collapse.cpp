#include"Collapse.h"

Collapse::Collapse() {
	x = -700;
	y = 0;
	texture = NULL;
	frame = 0;
	nRect.w = MAP_SIZE_X;
	nRect.h = MAP_SIZE_Y;
}

Collapse::~Collapse() {

}

void Collapse::setFrame() {
	for (int i = 0; i < COLLAPSE_FRAME; i++) {
		frameRect[i].x = i * COLLAPSE_WIDTH / 2;
		frameRect[i].y = 0;
		frameRect[i].w = COLLAPSE_WIDTH / 2;
		frameRect[i].h = COLLAPSE_HEIGHT / 2;
	}
}

void Collapse::showObj(SDL_Renderer* render, Map& map) {
	SDL_SetRenderDrawColor(render, 0, 0, 0, 0);
	if (frame == COLLAPSE_FRAME) frame = 0;
	setRect(x - map.getMapX(), y, COLLAPSE_WIDTH, COLLAPSE_HEIGHT);
	SDL_RenderCopy(render, texture, &frameRect[frame], &rect );
	nRect.x = x - MAP_SIZE_X - map.getMapX();
	nRect.y = 0;
	SDL_RenderFillRect(render, &nRect);
	frame++;
}


Position Collapse::getPos() {
	return Position(x, y);
}

void Collapse::move() {
	x = x + COLLAPSE_SPEED;
}