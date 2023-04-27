#include "MainMenuScreen.h"

bool MainMenuScreen::SetUpScreen()
{
	m_backgroundTexture = new Texture2D(m_renderer);

	if (!m_backgroundTexture->LoadFromFile("Images/Intro_Screen.png", SCREEN_WIDTH, SCREEN_HEIGHT))
	{
		std::cout << "Failed to load background texture!\n";
		return false;
	}

	LoadMusic("Music/Mario.mp3");
	if (Mix_PlayingMusic() == 0)
	{
		Mix_PlayMusic(m_music, -1);
	}

	return true;
}

MainMenuScreen::MainMenuScreen(SDL_Renderer* renderer) : Screen(renderer)
{
	SetUpScreen();
}

MainMenuScreen::~MainMenuScreen()
{
}

SCREENS MainMenuScreen::Update(float deltaTime, SDL_Event e)
{
	switch (e.type)
	{
	case SDL_KEYDOWN:

		switch (e.key.keysym.sym)
		{
		case SDLK_SPACE:
			return SCREEN_LEVEL1;
			break;
		}

	default:

		break;
		
	}
	return SCREEN_NONE;
}

void MainMenuScreen::Render()
{
	m_backgroundTexture->Render(Vector2D(0.0f, 0.0f), SDL_FLIP_NONE);
}
