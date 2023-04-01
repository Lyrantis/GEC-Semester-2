#include "game.h"

using namespace std;

Game::Game() {

}
Game::~Game() {

}

bool Game::SDLInit() {

	//Setup SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL did not initialise. Error: " << SDL_GetError();
		return false;
	}
	else
	{
		//setup passed so create window
		gameWindow = SDL_CreateWindow("Games Engine Creation",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
		//did the window get created?
		if (gameWindow == nullptr)
		{
			//window failed
			std::cout << "Window was not created. Error: " << SDL_GetError();
			return false;
		}

		gameRenderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED);
		if (gameRenderer != nullptr)
		{
			//init PNG loading
			int imageFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imageFlags) & imageFlags))
			{
				cout << "SDL_Image could not initialise. Error: " << IMG_GetError();
				return false;
			}

		}
		else
		{
			cout << "Renderer could not initialise. Error: " << SDL_GetError();
			return false;
		}

	}

	return true;

}
void Game::SDLClose() {

	//release the window
	SDL_DestroyWindow(gameWindow);
	gameWindow = nullptr;

	//quit SDL subsystems
	IMG_Quit();
	SDL_Quit();

	//Release Renderer
	SDL_DestroyRenderer(gameRenderer);
	gameRenderer = nullptr;

	delete screenManager;
	screenManager = nullptr;

	exit(0);

}

void Game::GameInit() {
	
	//check if sdl was setup correctly
	if (!SDLInit())
	{
		std::cout << "Init failed\n";
		SDLClose();
	}
	screenManager = new ScreenManager(gameRenderer, SCREEN_LEVEL1);
	g_old_time = SDL_GetTicks();

}

void Game::GameLoop() {

	GameInit();

	while (!quit) {

		quit = Update();
		Render();

	}

	SDLClose();

}

bool Game::Update() {

	new_time = SDL_GetTicks();
	startTime = chrono::high_resolution_clock::now();

	SDL_PollEvent(&e);

		switch (e.type) {

		case SDL_QUIT:

			return true;
			break;

		case SDL_KEYDOWN:

			switch (e.key.keysym.sym) {

			case SDLK_ESCAPE:

				return true;
				break;

			}
		}
	
	

	float deltaTime = (new_time - g_old_time) / 1000.0f;

	screenManager->Update(deltaTime, e);

	g_old_time = new_time;

	return false;

}

void Game::Draw() {

	gameSurface = SDL_GetWindowSurface(gameWindow);
	SDL_FillRect(gameSurface, NULL, SDL_MapRGB(gameSurface->format, 0x00, 0x00, 0x00));
	SDL_UpdateWindowSurface(gameWindow);

}

void Game::Render() {

	//Clear Screen
	SDL_SetRenderDrawColor(gameRenderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(gameRenderer);

	screenManager->Render();
	
	SDL_RenderPresent(gameRenderer);
}
