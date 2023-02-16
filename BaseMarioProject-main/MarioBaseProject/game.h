#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include "Constants.h"

class Game
{
public:

	SDL_Window* g_window = nullptr;
	SDL_Surface* g_surface = nullptr;
	SDL_Event e;
	bool quit = false;

	~Game();

	bool SDLInit();
	void SDLClose();

	void HandleInput();
	void Draw();
	void FrameSync();
	
	void GameLoop();
};

