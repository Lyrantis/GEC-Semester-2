#include "GameScreenLevel1.h"
#include <iostream>
#include "Texture2D.h"

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : Screen(renderer) {

	SetUpLevel();

}

GameScreenLevel1::~GameScreenLevel1() {

	delete m_backgroundTexture;
	m_backgroundTexture = nullptr;

}

void GameScreenLevel1::Render() {

}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e) {

}

bool GameScreenLevel1::SetUpLevel() {

}