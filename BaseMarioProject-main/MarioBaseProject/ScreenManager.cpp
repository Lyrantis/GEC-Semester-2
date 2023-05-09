#include "ScreenManager.h"
#include "MainLevel.h"
#include "MainMenuScreen.h"
#include "ScoreScreen.h"


ScreenManager::ScreenManager(SDL_Renderer* renderer, int startScreen) {

	m_renderer = renderer;
	m_currentScreen = nullptr;
	m_currentlevel = startScreen;

	ChangeScreen();
}

ScreenManager::~ScreenManager() {

	m_renderer = nullptr;
	delete m_currentScreen;
	m_currentScreen = nullptr;
}

void ScreenManager::Render() {

	m_currentScreen->Render();
}

void ScreenManager::Update(float deltaTime,  SDL_Event e) {

	bool changeLevel =  m_currentScreen->Update(deltaTime, e);

	if (changeLevel)
	{
		Mix_FreeMusic(m_currentScreen->m_music);

		if (m_currentScreen->WinOrLose())
		{
			m_currentlevel++;
		}
		else
		{
			m_currentlevel = 8;
		}
		ChangeScreen();
	}
	
}

void ScreenManager::ChangeScreen() 
{

	if (m_currentlevel >= m_levelCount)
	{
		m_currentlevel = 0;
	}

	if (m_currentScreen != nullptr) {
		delete m_currentScreen;
		m_currentScreen = nullptr;
	}

	Screen* tempScreen;

	switch (m_currentlevel)
	{
	case 0:

		ScoreSystem::Instance()->ResetScores();
		tempScreen = new MainMenuScreen(m_renderer);
		m_currentScreen = (Screen*)tempScreen;

		break;

	case 8:

		tempScreen = new ScoreScreen(m_renderer);
		m_currentScreen = (Screen*)tempScreen;

		break;

	default:

		tempScreen = new MainLevel(m_renderer, m_currentlevel);
		m_currentScreen = (Screen*)tempScreen;

		break;
	}

	tempScreen = nullptr;
}
