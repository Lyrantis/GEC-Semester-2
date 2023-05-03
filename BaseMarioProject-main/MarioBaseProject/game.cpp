#include "game.h"

using namespace std;

Game::Game() 
{
	
}
Game::~Game() 
{
}

bool Game::SDLInit() 
{
	//Setup SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
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

		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			cout << "Mixer failed to initialise. Error: " << Mix_GetError();
			return false;
		}

		if (TTF_Init() == -1)
		{
			cout << "TTF failed to initialise. Error: " << TTF_GetError();
		}
	}

	return true;

}
void Game::SDLClose()
{

	//release the window
	SDL_DestroyWindow(gameWindow);
	gameWindow = nullptr;

	//quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	Mix_Quit();
	TTF_Quit();

	//Release Renderer
	SDL_DestroyRenderer(gameRenderer);
	gameRenderer = nullptr;

	delete screenManager;
	screenManager = nullptr;

	exit(0);

}

void Game::GameInit() 
{
	
	//check if sdl was setup correctly
	if (!SDLInit())
	{
		std::cout << "Init failed\n";
		SDLClose();
	}
	screenManager = new ScreenManager(gameRenderer, SCREEN_MAINMENU);
	g_old_time = SDL_GetTicks();

	leaderboardNames = new std::string[5];
	leaderboardScores = new std::string[5];
	ScoreSystem::Instance()->LoadHighscores(leaderboardNames, leaderboardScores);

}

void Game::GameLoop() 
{

	GameInit();

	while (!quit) {

		quit = Update();
		Render();

	}

	SDLClose();

}

bool Game::Update() 
{

	new_time = SDL_GetTicks();

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


void Game::Render() 
{

	//Clear Screen
	SDL_SetRenderDrawColor(gameRenderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(gameRenderer);

	screenManager->Render();
	
	SDL_RenderPresent(gameRenderer);
}
