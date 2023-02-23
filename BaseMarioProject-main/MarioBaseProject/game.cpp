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

			//load Image
			gameTexture = LoadTextureFromFile("Images/test.bmp");

			if (gameTexture == nullptr) {

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

	//Clear Texture 
	FreeTexture();

	//Release Renderer
	SDL_DestroyRenderer(gameRenderer);
	gameRenderer = nullptr;

	exit(0);

}

void Game::GameLoop() {

	//check if sdl was setup correctly
	if (!SDLInit())
	{
		std::cout << "Init failed\n";
		SDLClose();
	}



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
				cout << "Pressed\n";
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
				cout << "Released\n";
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
		imageY -= 5;
	}
	if (keyStates["s"] == true) {
		imageY += 5;
	}
	if (keyStates["a"] == true) {
		imageX -= 5;
	}
	if (keyStates["d"] == true) {
		imageX += 5;
	}
	
}

void Game::Draw() {

	gameSurface = SDL_GetWindowSurface(gameWindow);
	SDL_FillRect(gameSurface, NULL, SDL_MapRGB(gameSurface->format, 0x00, 0x00, 0x00));
	SDL_UpdateWindowSurface(gameWindow);

}

void Game::Render() {

	//Clear Screen
	SDL_SetRenderDrawColor(gameRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gameRenderer);

	SDL_Rect renderLocation = { imageX, imageY, 100, 100 };

	switch (imageFlipped)
	{
	case true:

		SDL_RenderCopyEx(gameRenderer, gameTexture, NULL, &renderLocation, 0, NULL, SDL_FLIP_VERTICAL);
		break;
	case false:
		SDL_RenderCopyEx(gameRenderer, gameTexture, NULL, &renderLocation, 0, NULL, SDL_FLIP_NONE);
	default:
		break;
	}
	

	SDL_RenderPresent(gameRenderer);
}

SDL_Texture* Game::LoadTextureFromFile(std::string path) {

	SDL_Texture* p_texture = nullptr;

	//Load image
	SDL_Surface* p_surface = IMG_Load(path.c_str());

	if (p_surface != nullptr) {

		//create the texture from the pixels on the surface
		p_texture = SDL_CreateTextureFromSurface(gameRenderer, p_surface);
		if (p_texture == nullptr)
		{
			cout << "Unable to create texture from surface. Error: " << SDL_GetError();
		}
		//remove the loaded surface now that we have a texture
		SDL_FreeSurface(p_surface);

	}
	else {
		cout << "Unable to create texture from surface. Error: " << IMG_GetError();
	}

	return p_texture;
}

void Game::FreeTexture() {

	if (gameTexture != nullptr) {

		SDL_DestroyTexture(gameTexture);
		gameTexture = nullptr;

	}
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