#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include <Windows.h>
#include <chrono>
#include "Constants.h"

class Game
{

private:

	const float fps = 60.0f;
	const float fixedDeltaTime = 1000.0f / fps;
	int frameCount = 0;
	int secondsElapsed = 0;
	std::chrono::high_resolution_clock::time_point startTime;
	std::chrono::high_resolution_clock::time_point endTime;
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

