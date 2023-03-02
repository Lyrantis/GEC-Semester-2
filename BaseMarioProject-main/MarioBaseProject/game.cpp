#include "game.h"

using namespace std;
Game::~Game() {

	delete playerTexture;
	delete brickTexture;

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

			playerTexture = new Texture2D(gameRenderer);

			if (!playerTexture->LoadFromFile("Images/test.bmp", 64, 64)) {

				return false;
			}

			brickTexture = new Texture2D(gameRenderer);

			if (!brickTexture->LoadFromFile("Images/brick.png", 32, 32)) {

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

	exit(0);

}

void Game::GameInit() {
	
	//check if sdl was setup correctly
	if (!SDLInit())
	{
		std::cout << "Init failed\n";
		SDLClose();
	}

	Player player = Player(0, 0, 64);

	bricks.push_back(Brick(500, 500, 32));
	bricks.push_back(Brick(532, 500, 32));
	bricks.push_back(Brick(564, 500, 32));
}

void Game::GameLoop() {

	GameInit();

	while (!quit) {

		startTime = chrono::high_resolution_clock::now();

		quit = Update();
		//Draw();
		Render();
		FrameSync();

	}

	SDLClose();

}

bool Game::Update() {

	while (SDL_PollEvent(&e)) {

		switch (e.type) {

		case SDL_QUIT:

			return true;
			break;

		case SDL_KEYDOWN:

			switch (e.key.keysym.sym) {

			case SDLK_ESCAPE:

				return true;
				break;

			case SDLK_SPACE:

				if (imageFlipped) {
					imageFlipped = false;
				}
				else {
					imageFlipped = true;
				}

				break;

			case SDLK_w:

				keyStates["w"] = true;
				break;

			case SDLK_s:

				keyStates["s"] = true;
				break;

			case SDLK_a:

				keyStates["a"] = true;
				break;

			case SDLK_d:

				keyStates["d"] = true;
				break;
			}

			break;

		case SDL_KEYUP:

			switch (e.key.keysym.sym) {

			case SDLK_w:

				keyStates["w"] = false;
				break;

			case SDLK_s:

				keyStates["s"] = false;
				break;

			case SDLK_a:

				keyStates["a"] = false;
				break;

			case SDLK_d:

				keyStates["d"] = false;
				break;
			
			}

			break;

		}
	}

	HandleInput();

	return false;

}

void Game::HandleInput() {

	if (keyStates["w"] == true) {
		player.location.y -= player.speed;
	}
	if (keyStates["s"] == true) {
		player.location.y += player.speed;
	}
	if (keyStates["a"] == true) {
		player.location.x -= player.speed;
	}
	if (keyStates["d"] == true) {
		player.location.x += player.speed;
	}
	
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

	playerTexture->Render(Vector2D(player.location.x, player.location.y), SDL_FLIP_NONE);
	for (int i = 0; i < bricks.size(); i++) {

		brickTexture->Render(Vector2D(bricks[i].location.x, bricks[i].location.y), SDL_FLIP_NONE);
	}
	
	

	SDL_RenderPresent(gameRenderer);
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
	}
}