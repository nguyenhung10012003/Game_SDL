#pragma once

#ifndef MAIN_H
#define MAIN_H

#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<Windows.h>

using namespace std;

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 600

static const char* WINDOW_TITLE = "THE FANTASY";

const int FPS = 20;
const int DELAY_TIME = 1000 / FPS;

void startSDL();
SDL_Window* creatWindow();
SDL_Renderer* creatRenderer(SDL_Window* window);


#endif 
#undef main