#include "GameScreenLevel1.h"
#include <iostream>
#include "Texture2D.h"
#include "PowBlock.h"

using namespace std;

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : Screen(renderer) {

	m_level_map = nullptr;
	SetUpLevel();

}

GameScreenLevel1::~GameScreenLevel1() {

	delete m_backgroundTexture;
	m_backgroundTexture = nullptr;

	delete mario;
	mario = nullptr;

	delete luigi;
	luigi = nullptr;

	delete m_pow_block;
	m_pow_block = nullptr;

}

void GameScreenLevel1::Render() {

	m_backgroundTexture->Render(Vector2D(0.0f, m_background_yPos), SDL_FLIP_NONE);

	mario->Render();
	luigi->Render();

	m_pow_block->Render();

}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e) 
{

	/*
 * do the screen shake if required
 */
	if (m_screenshake)
	{
		m_shake_time -= deltaTime;
		m_wobble++;
		m_background_yPos = sin(m_wobble);
		m_background_yPos *= 3.0f;

		//end shake after duration
		if (m_shake_time <= 0.0f)
		{
			m_shake_time = false;
			m_background_yPos = 0.0f;
		}
	}


	mario->Update(deltaTime, e);
	luigi->Update(deltaTime, e);

	UpdatePOWBlock();

	if (Collisions::Instance()->Box(mario->GetCollisionBox(), luigi->GetCollisionBox())) {
		std::cout << "Box collision" << endl;
	}

}

void GameScreenLevel1::UpdatePOWBlock() {

	if (Collisions::Instance()->Box(mario->GetCollisionBox(), m_pow_block->GetCollisionBox())) 
	{
		if (m_pow_block->IsAvailable())
		{
			//collided while jumping
			if (mario->IsJumping())
			{
				DoScreenShake();
				m_pow_block->TakeHit();
				mario->CancelJump();
			}

		}
	}

	if (Collisions::Instance()->Box(luigi->GetCollisionBox(), m_pow_block->GetCollisionBox()))
	{
		if (m_pow_block->IsAvailable())
		{
			//collided while jumping
			if (luigi->IsJumping())
			{
				//DoScreenShake();
				m_pow_block->TakeHit();
				luigi->CancelJump();
			}

		}
	}
}

bool GameScreenLevel1::SetUpLevel() {

	m_backgroundTexture = new Texture2D(m_renderer);

	if (!m_backgroundTexture->LoadFromFile("Images/BackgroundMB.png", SCREEN_WIDTH, SCREEN_HEIGHT)) {

		cout << "Failed to load background texture!\n";
		return false;
	}

	SetLevelMap();

	mario = new Mario(m_renderer, "Images/Mario.png", Vector2D(0, 0), 64, 84, m_level_map);
	luigi = new Luigi(m_renderer, "Images/Luigi.png", Vector2D(100, 0), 64, 84, m_level_map);

	m_pow_block = new PowBlock(m_renderer, m_level_map);

	m_screenshake = false;
	m_background_yPos = 0.0f;

}

void GameScreenLevel1::SetLevelMap() {

	int map[MAP_HEIGHT][MAP_WIDTH] = { 
					  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
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

void GameScreenLevel1::DoScreenShake() 
{
	m_screenshake = true;
	m_shake_time = SHAKE_DURATION;
	m_wobble = 0.0f;

}
