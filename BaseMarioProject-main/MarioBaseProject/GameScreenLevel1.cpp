#include "GameScreenLevel1.h"
#include <iostream>
#include "Texture2D.h"

using namespace std;

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : Screen(renderer) {

	SetUpLevel();

	m_level_map = nullptr;


}

GameScreenLevel1::~GameScreenLevel1() {

	delete m_backgroundTexture;
	m_backgroundTexture = nullptr;

	delete mario;
	mario = nullptr;

	delete luigi;
	luigi = nullptr;

}

void GameScreenLevel1::Render() {

	m_backgroundTexture->Render(Vector2D(), SDL_FLIP_NONE);

	mario->Render();
	luigi->Render();

}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e) {

	mario->Update(deltaTime, e);
	luigi->Update(deltaTime, e);

	if (Collisions::Instance()->Box(mario->GetCollisionBox(), luigi->GetCollisionBox())) {
		std::cout << "Box collision" << endl;
	}

}

bool GameScreenLevel1::SetUpLevel() {

	m_backgroundTexture = new Texture2D(m_renderer);

	if (!m_backgroundTexture->LoadFromFile("Images/test.bmp", SCREEN_WIDTH, SCREEN_HEIGHT)) {

		cout << "Failed to load background texture!\n";
		return false;
	}

	mario = new Mario(m_renderer, "Images/Mario.png", Vector2D(0, 0), 32, 42, m_level_map);
	luigi = new Luigi(m_renderer, "Images/Luigi.png", Vector2D(100, 0), 32, 42, m_level_map);
}

void GameScreenLevel1::SetLevelMap() {

	int map[MAP_HEIGHT][MAP_WIDTH] = { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0 },
					  { 1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0 },
					  { 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };

	//clear any old maps
	if (m_level_map != nullptr)
	{
		delete m_level_map;
	}

	//set the new one
	m_level_map = new LevelMap(map);

}
