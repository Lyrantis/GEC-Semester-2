#include "ScreenManager.h"
#include "Screen.h"
#include "GameScreenLevel1.h"
#include "MainMenuScreen.h"
#include "ScreenManager.h"

ScreenManager::ScreenManager(SDL_Renderer* renderer, SCREENS startScreen) {

	m_renderer = renderer;
	m_currentScreen = nullptr;

	ChangeScreen(startScreen);
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

	SCREENS screenToChangeTo =  m_currentScreen->Update(deltaTime, e);

	if (screenToChangeTo != SCREEN_NONE)
	{
		m_currentScreen->
		ChangeScreen(screenToChangeTo);
	}
	
}

void ScreenManager::ChangeScreen(SCREENS newScreen) {

	if (m_currentScreen != nullptr) {
		delete m_currentScreen;
	}

	Screen* tempScreen;

	switch (newScreen)
	{
	case SCREEN_INTRO:
		break;
	case SCREEN_MAINMENU:
		tempScreen = new MainMenuScreen(m_renderer);
		m_currentScreen = (Screen*)tempScreen;
		tempScreen = nullptr;
		break;
	case SCREEN_LEVEL1:
		tempScreen = new GameScreenLevel1(m_renderer);
		m_currentScreen = (Screen*)tempScreen;
		tempScreen = nullptr;
		break;
	case SCREEN_LEVEL2:
		break;
	case SCREEN_GAMEOVER:
		break;
	case SCREEN_HIGHSCORES:
		break;
	default:
		break;
	}
}
