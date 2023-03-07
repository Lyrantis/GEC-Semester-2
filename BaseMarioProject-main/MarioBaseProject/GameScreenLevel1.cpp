#include "GameScreenLevel1.h"
#include <iostream>
#include "Texture2D.h"

using namespace std;

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : Screen(renderer) {

	SetUpLevel();

}

GameScreenLevel1::~GameScreenLevel1() {

	delete m_backgroundTexture;
	m_backgroundTexture = nullptr;

}

void GameScreenLevel1::Render() {

	m_backgroundTexture->Render(Vector2D(), SDL_FLIP_NONE);
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e) {

}

bool GameScreenLevel1::SetUpLevel() {

	m_backgroundTexture = new Texture2D(m_renderer);

	if (!m_backgroundTexture->LoadFromFile("Images/test.bmp", SCREEN_WIDTH, SCREEN_HEIGHT)) {

		cout << "Failed to load background texture!\n";
		return false;
	}
}