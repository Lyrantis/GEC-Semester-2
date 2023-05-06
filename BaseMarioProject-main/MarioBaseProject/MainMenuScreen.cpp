#include "MainMenuScreen.h"

bool MainMenuScreen::SetUpScreen()
{
	m_backgroundTexture = new Texture2D(m_renderer);

	if (!m_backgroundTexture->LoadFromFile("Images/TitleScreen.png", SCREEN_WIDTH, SCREEN_HEIGHT))
	{
		std::cout << "Failed to load background texture!\n";
		return false;
	}

	LoadMusic("Music/Mario.mp3");
	if (Mix_PlayingMusic() == 0)
	{
		Mix_PlayMusic(m_music, -1);
	}

	m_text = new TextRenderer(m_renderer);

	SDL_Color colour;
	colour.r = 255; colour.g = 255; colour.b = 255; colour.a = 255;
	if (!m_text->LoadFont("Fonts/PixelEmulator.ttf", 24, m_textMessage, colour))
	{
		std::cout << "Failed to load font!\n";
		return false;
	}

	return true;
}

MainMenuScreen::MainMenuScreen(SDL_Renderer* renderer) : Screen(renderer)
{
	SetUpScreen();
}

MainMenuScreen::~MainMenuScreen()
{
	delete m_text;
	m_text = nullptr;
}

bool MainMenuScreen::Update(float deltaTime, SDL_Event e)
{
	switch (e.type)
	{
	case SDL_KEYDOWN:

		switch (e.key.keysym.sym)
		{
		case SDLK_SPACE:
			return true;
			break;

		case SDLK_p:

			m_text->SetMessage("Hello");
		}

	default:

		break;
		
	}
	return false;
}

void MainMenuScreen::Render()
{
	m_backgroundTexture->Render(Vector2D(0.0f, 0.0f), SDL_FLIP_NONE);
	m_text->Render((SCREEN_WIDTH / 2) - 250, 650);
}
