#include "ScoreScreen.h"
#include "ScoreSystem.h"

bool ScoreScreen::SetUpScreen()
{
	m_backgroundTexture = new Texture2D(m_renderer);

	if (!m_backgroundTexture->LoadFromFile("Images/Score_Board_Screen.png", SCREEN_WIDTH, SCREEN_HEIGHT))
	{
		std::cout << "Failed to load Background Texture\n";
		return false;
	}
	

	m_pointerTexture = new Texture2D(m_renderer);
	if (!m_pointerTexture->LoadFromFile("Images/LetterSelect.png", 50, 50))
	{
		std::cout << "Failed to load pointer Texture\n";
		return false;
	}
	

	SDL_Color colour;
	colour.r = 255; colour.g = 255; colour.b = 255; colour.a = 255;

	m_nameText = new TextRenderer(m_renderer);

	if (!m_nameText->LoadFont("Fonts/PixelEmulator.ttf", 32, m_name, colour))
	{
		std::cout << "Failed to load font!\n";
		return false;
	}

	m_pointerRect = new Rect2D(215, 215, 50, 50);

	for (int i = 0; i < 5; i++)
	{
		m_highScoreNameTexts[i] = new TextRenderer(m_renderer);

		if (!m_highScoreNameTexts[i]->LoadFont("Fonts/PixelEmulator.ttf", 32, ScoreSystem::Instance()->leaderboardNames[i], colour))
		{
			std::cout << "Failed to load font!\n";
			return false;
		}

		m_highScoreTexts[i] = new TextRenderer(m_renderer);

		if (!m_highScoreTexts[i]->LoadFont("Fonts/PixelEmulator.ttf", 32, ScoreSystem::Instance()->leaderboardScores[i], colour))
		{
			std::cout << "Failed to load font!\n";
			return false;
		}
	}

	return true;
}

ScoreScreen::ScoreScreen(SDL_Renderer* renderer) : Screen(renderer)
{
	SetUpScreen();
}

ScoreScreen::~ScoreScreen()
{

}

SCREENS ScoreScreen::Update(float deltaTime, SDL_Event e)
{
	if (nameEntered)
	{
		timeToChange -= deltaTime;

		if (timeToChange <= 0.0f)
		{
			return SCREEN_MAINMENU;
		}
	}
	else
	{
		switch (e.type)
		{
		case SDL_KEYDOWN:

			switch (e.key.keysym.sym)
			{
			case SDLK_SPACE:

				if (!keyStates[4])
				{
					keyStates[4] = true;

					if (m_pointerPos == 28)
					{
						if (m_name[currentLetter] == '-' && currentLetter > 0)
						{
							currentLetter--;
							m_name[currentLetter] = '-';
						}
						else
						{
							m_name[currentLetter] = '-';
						}

						m_nameText->SetMessage(m_name);
					}
					else if (m_pointerPos == 29)
					{
						//Done
					}
					else
					{
						m_name[currentLetter] = characters[m_pointerPos];
						m_nameText->SetMessage(m_name);

						if (currentLetter < 2)
						{
							currentLetter++;
						}
					}
				}

				break;

			case SDLK_BACKSPACE:

				if (!keyStates[5])
				{
					keyStates[5] = true;

					if (m_name[currentLetter] == '-' && currentLetter > 0)
					{
						currentLetter--;
						m_name[currentLetter] = '-';
					}
					else
					{
						m_name[currentLetter] = '-';
					}

					m_nameText->SetMessage(m_name);

				}

				break;

			case SDLK_RETURN:

				if (!keyStates[6])
				{
					keyStates[6] = true;
					nameEntered = true;
					ScoreSystem::Instance()->UpdateLeaderBoard(m_name);

					for (int i = 0; i < 5; i++)
					{
						m_highScoreNameTexts[i]->SetMessage(ScoreSystem::Instance()->leaderboardNames[i]);
						m_highScoreTexts[i]->SetMessage(ScoreSystem::Instance()->leaderboardScores[i]);
					}
					//Done
				}

				break;

			case SDLK_w: case SDLK_UP:

				if (!keyStates[0])
				{
					keyStates[0] = true;

					m_pointerPos -= 10;
					m_pointerRect->y -= m_letterWidth;

					if (m_pointerPos < 0)
					{
						m_pointerPos += 30;
						m_pointerRect->y += (3 * m_letterWidth);
					}
				}

				break;

			case SDLK_s: case SDLK_DOWN:

				if (!keyStates[1])
				{
					keyStates[1] = true;

					m_pointerPos += 10;
					m_pointerRect->y += m_letterWidth;

					if (m_pointerPos > 30)
					{
						m_pointerPos -= 30;
						m_pointerRect->y -= (3 * m_letterWidth);
					}
				}

				break;

			case SDLK_a: case SDLK_LEFT:

				if (!keyStates[2])
				{
					keyStates[2] = true;

					if (m_pointerPos % 10 == 0)
					{
						m_pointerPos += 9;
						m_pointerRect->x += (9 * m_letterWidth);
					}
					else
					{
						m_pointerPos--;
						m_pointerRect->x -= m_letterWidth;
					}
				}


				break;

			case SDLK_d: case SDLK_RIGHT:

				if (!keyStates[3])
				{
					keyStates[3] = true;

					if ((m_pointerPos + 1) % 10 == 0)
					{
						m_pointerPos -= 9;
						m_pointerRect->x -= (9 * m_letterWidth);
					}
					else
					{
						m_pointerPos++;
						m_pointerRect->x += m_letterWidth;
					}

				}

				break;
			}

			break;

		case SDL_KEYUP:

			switch (e.key.keysym.sym)
			{
			case SDLK_SPACE:

				keyStates[4] = false;

				break;

			case SDLK_BACKSPACE:

				keyStates[5] = false;

				break;

			case SDLK_KP_ENTER:

				keyStates[6] = false;
				break;

			case SDLK_w: case SDLK_UP:

				keyStates[0] = false;

				break;

			case SDLK_s: case SDLK_DOWN:

				keyStates[1] = false;

				break;

			case SDLK_a: case SDLK_LEFT:

				keyStates[2] = false;

				break;

			case SDLK_d: case SDLK_RIGHT:

				keyStates[3] = false;

				break;
			}

			break;

		default:

			break;

		}
	}
	
	return SCREEN_NONE;
}

void ScoreScreen::Render()
{
	m_backgroundTexture->Render(Vector2D(0.0f, 0.0f), SDL_FLIP_NONE);
	m_pointerTexture->Render(Rect2D(0, 0, 15, 15), *m_pointerRect, SDL_FLIP_NONE);
	
	m_nameText->Render((SCREEN_WIDTH / 2) - 20, 124);

	for (int i = 0; i < 5; i++)
	{
		m_highScoreTexts[i]->Render(420, 544 + (i * 64));
		m_highScoreNameTexts[i]->Render(650, 544 + (i * 64));
	}

}
