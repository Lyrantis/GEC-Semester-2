#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include <vector>
#include <string.h>
#include <map>
#include <Windows.h>
#include "Constants.h"
#include "Texture2D.h"
#include "ScreenManager.h"
#include "Character.h"
#include "Mario.h"
#include "Luigi.h"
#include "Koopa.h"
#include "FighterFly.h"
#include "Coin.h"
#include "Collisions.h"
#include <time.h>
#include "Screen.h"
#include "Commons.h"
#include "LevelMap.h"


using namespace std;

class Game
{

private:

	ScreenManager* screenManager;

	const float fps = 60.0f;
	const float fixedDeltaTime = 1000.0f / fps;
	int frameCount = 0;
	int secondsElapsed = 0;

	Uint32 g_old_time;
	Uint32 new_time;

	map<string, bool> keyStates{
		{"w", false},
		{"a", false},
		{"s", false},
		{"d", false},
		{"space", false},
		{"shift", false}
	};


public:

	SDL_Window* gameWindow = nullptr;
	SDL_Surface* gameSurface = nullptr;
	SDL_Renderer* gameRenderer = nullptr;

	SDL_Event e;

	bool quit = false;
	Game();
	~Game();

	bool SDLInit();
	void SDLClose();

	void GameInit();

	void GameLoop();
	bool Update();
	void Render();

	void LoadMusic(string path);
};

