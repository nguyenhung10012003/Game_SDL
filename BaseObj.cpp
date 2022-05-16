#include"Object.h"

BaseObject::BaseObject() {
	texture = NULL;
	rect.x = 0;
	rect.y = 0;
	rect.h = 0;
	rect.w = 0;
}

BaseObject::~BaseObject() {
	SDL_DestroyTexture(texture);
}

void BaseObject::loadImage(SDL_Renderer* render, const char* file) {
	texture = IMG_LoadTexture(render, file);
	if (texture == NULL) {
		cout << "Cann't load Image from " << file << SDL_GetError() << endl;
		return;
	}
}

void BaseObject::setRect(const int& x = 0, const int& y = 0, const int& w = 0, const int& h = 0) {
	rect.x = x;
	rect.y = y;
	rect.h = h;
	rect.w = w;
}

void BaseObject::show(SDL_Renderer* render) {
	SDL_RenderCopy(render, texture, NULL, &rect);
}