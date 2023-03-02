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
#include "Player.h"
#include "Brick.h"

using namespace std;

class Game
{

private:

	const float fps = 60.0f;
	const float fixedDeltaTime = 1000.0f / fps;
	int frameCount = 0;
	int secondsElapsed = 0;
	chrono::high_resolution_clock::time_point startTime;
	chrono::high_resolution_clock::time_point endTime;

	bool imageFlipped = false;
	float imageX = 0;
	float imageY = 0;

	Player player; 

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
	SDL_Texture* playerTexture = nullptr;

	string brickTexturePath = "Images/brick.png";
	SDL_Texture* brickTexture = nullptr;

	SDL_Event e;

	bool quit = false;

	~Game();

	bool SDLInit();
	void SDLClose();

	void GameInit();

	void GameLoop();
	bool Update();
	void HandleInput();
	void Draw();

	void Render();
	SDL_Texture* LoadTextureFromFile(string path);
	void FreeTexture();

	void FrameSync();

};

