#include "game.h"

using namespace std;
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
		g_window = SDL_CreateWindow("Games Engine Creation",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
		//did the window get created?
		if (g_window == nullptr)
		{
			//window failed
			std::cout << "Window was not created. Error: " << SDL_GetError();
			return false;
		}
	}

	return true;

}
void Game::SDLClose() {

	//release the window
	SDL_DestroyWindow(g_window);
	g_window = nullptr;

	//quit SDL subsystems
	IMG_Quit();
	SDL_Quit();

	exit(0);

}

void Game::HandleInput() {

	while (SDL_PollEvent(&e)) {

		if (e.type == SDL_QUIT) {
			quit = true;
		}
	}

}

void Game::Draw() {

	g_surface = SDL_GetWindowSurface(g_window);
	SDL_FillRect(g_surface, NULL, SDL_MapRGB(g_surface->format, 0x00, 0x00, 0x00));
	SDL_UpdateWindowSurface(g_window);

}

void Game::GameLoop() {

	//check if sdl was setup correctly
	if (!SDLInit())
	{
		std::cout << "Init failed\n";
		SDLClose();
	}

	
	
	while (!quit) {

		startTime = std::chrono::high_resolution_clock::now();

		HandleInput();
		Draw();
		FrameSync();
		
	}

	SDLClose();

}

void Game::FrameSync() {

	endTime = chrono::high_resolution_clock::now();
	
	chrono::duration<double> timeDuration = chrono::duration_cast<chrono::milliseconds>(endTime - startTime);

	int deltaTime = timeDuration.count();

	if (deltaTime < fixedDeltaTime) {

		Sleep(fixedDeltaTime - deltaTime);
	}

	frameCount++;

	if (frameCount >= 60) {

		secondsElapsed++;
		frameCount = 0;
		cout << "Tick\n";
	}
}