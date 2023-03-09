#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include <vector>
#include <string.h>
#include <map>
#include <Windows.h>
#include <chrono>
#include "Constants.h"
#include "Commons.h"
#include "Texture2D.h"
#include "ScreenManager.h"
#include "Player.h"
#include "Brick.h"
#include <time.h>

using namespace std;

class Game
{

private:

	ScreenManager* screenManager;

	const float fps = 60.0f;
	const float fixedDeltaTime = 1000.0f / fps;
	int frameCount = 0;
	int secondsElapsed = 0;
	chrono::high_resolution_clock::time_point startTime;
	chrono::high_resolution_clock::time_point endTime;

	Uint32 g_old_time;
	Uint32 new_time;

	bool imageFlipped = false;
	float imageX = 0;
	float imageY = 0;

	Player* player; 

	vector<Brick> bricks;

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
	Texture2D* playerTexture = nullptr;

	string brickTexturePath = "Images/brick.png";
	Texture2D* brickTexture = nullptr;

	SDL_Event e;

	bool quit = false;
	Game();
	~Game();

	bool SDLInit();
	void SDLClose();

	void GameInit();

	void GameLoop();
	bool Update();
	void HandleInput();
	void Draw();

	void Render();

	void FrameSync();

};

