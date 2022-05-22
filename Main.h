#pragma once

#ifndef MAIN_H
#define MAIN_H

#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>
#include<Windows.h>

using namespace std;

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 600
#define SOUND_RUN_PATH "Chapter1\\Sound\\step1.wav"
#define SOUND_COLLECT_PATH "Chapter1\\Sound\\collect.wav"
#define BGM_PATH "Chapter1\\Sound\\BGM.mp3"
#define GAMEOVER_SOUND_PATH "Chapter1\\Sound\\gameOver.mp3"
#define WON_SOUND_PATH "Chapter1\\Sound\\won.mp3"

static const char* WINDOW_TITLE = "THE FANTASY";

const int FPS = 25;
const int DELAY_TIME = 1000 / FPS;

void startSDL();
SDL_Window* creatWindow();
SDL_Renderer* creatRenderer(SDL_Window* window);

#endif 
#undef main