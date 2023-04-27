#include "GameScreenLevel1.h"
#include <iostream>
#include "Texture2D.h"
#include "PowBlock.h"

using namespace std;

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : Screen(renderer) 
{
	m_level_map = nullptr;
	SetUpLevel();

}

GameScreenLevel1::~GameScreenLevel1() 
{

	delete mario;
	mario = nullptr;

	delete luigi;
	luigi = nullptr;

	for (int i = 0; i < m_enemies.size(); i++)
	{
		delete m_enemies[i];
	}

	m_enemies.clear();

	delete m_pow_block;
	m_pow_block = nullptr;
}

void GameScreenLevel1::Render() 
{
	m_backgroundTexture->Render(Vector2D(0.0f, m_background_yPos), SDL_FLIP_NONE);

	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->Render();
	}

	mario->Render();
	luigi->Render();

	for (int i = 0; i < m_coins.size(); i++)
	{
		m_coins[i]->Render();
	}

	m_pow_block->Render();

}

SCREENS GameScreenLevel1::Update(float deltaTime, SDL_Event e) 
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

	if (mario->GetActive())
	{
		mario->Update(deltaTime, e);
	}
	
	if (luigi->GetActive())
	{
		luigi->Update(deltaTime, e);
	}

	if (!mario->GetActive() && !luigi->GetActive())
	{
		SDL_Quit();
	}

	UpdateCoins(deltaTime);
	UpdateEnemies(deltaTime, e);
	UpdatePOWBlock(deltaTime);

	return SCREEN_NONE;
}

void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e)
{
	if (!m_enemies.empty())
	{
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < m_enemies.size(); i++)
		{
			//is the enemy off screen to the left / right?
			if (m_enemies[i]->GetPosition().x < 0.0f || m_enemies[i]->GetPosition().x > SCREEN_WIDTH - (float)(m_enemies[i]->GetSize().x))
			{
				//check if the enemy is on the bottom row of tiles
				if (m_enemies[i]->GetPosition().y >= SCREEN_HEIGHT - (TILE_HEIGHT + m_enemies[i]->GetSize().y))
				{
					m_enemies[i]->Die();
				}
				else
				{
					m_enemies[i]->FlipDirection();
				}
			}

			m_enemies[i]->Update(deltaTime, e);

			//check to see if enemy collides with player
			if ((m_enemies[i]->GetPosition().y > 300.0f || m_enemies[i]->GetPosition().y <= 64.0f) && (m_enemies[i]->GetPosition().x < 64.0f || m_enemies[i]->GetPosition().x > SCREEN_WIDTH - 96.0f))
			{
				//ignore collisions if behind pipe
			}
			else
			{
				if (Collisions::Instance()->Circle(m_enemies[i]->GetCollisionRadius(), mario->GetCollisionRadius()))
				{

					if (m_enemies[i]->GetInjured())
					{
						m_enemies[i]->Die();
						mario->AddScore(m_enemies[i]->GetScoreValue());
					}
					else
					{
						mario->Die(deltaTime);
					}
				}

				if (Collisions::Instance()->Circle(m_enemies[i]->GetCollisionRadius(), luigi->GetCollisionRadius()))
				{
					if (m_enemies[i]->GetInjured())
					{
						m_enemies[i]->Die();
						luigi->AddScore(m_enemies[i]->GetScoreValue());
					}
					else
					{
						luigi->Die(deltaTime);
					}
				}
			}

			//if the enemy is no longer alive then schedule it for deletion
			if (!m_enemies[i]->GetAlive())
			{
				enemyIndexToDelete = i;
			}
		}

		//remove dead enemies -1 each update

		if (enemyIndexToDelete != -1)
		{
			m_enemies.erase(m_enemies.begin() + enemyIndexToDelete);
		}
	}

	m_enemy_wave_time -= deltaTime;

	if (m_enemy_wave_time <= 0.0f)
	{
		m_enemy_wave_time = INITIAL_ENEMY_WAVE_TIME;

		CreateKoopa(Vector2D(0, TILE_HEIGHT), FACING_RIGHT);
		CreateKoopa(Vector2D(SCREEN_WIDTH - KOOPA_WIDTH, TILE_HEIGHT), FACING_LEFT);
	}
}

void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction)
{
	m_enemies.push_back(new Koopa(m_renderer, "Images/Koopa.png", position, direction, m_level_map));
}

void GameScreenLevel1::CreateFly(Vector2D position, FACING direction)
{
	m_enemies.push_back(new FighterFly(m_renderer, "Images/Fighter_Fly.png", position, direction, m_level_map));
}

void GameScreenLevel1::CreateCoin(Vector2D position)
{
	m_coins.push_back(new Coin(m_renderer, "Images/Coin.png", position, m_level_map));
}

void GameScreenLevel1::UpdateCoins(float deltaTime)
{
	if (!m_coins.empty())
	{
		int coinIndexToDelete = -1;
		for (int i = 0; i < m_coins.size(); i++)
		{
			m_coins[i]->Update(deltaTime);

			if (Collisions::Instance()->Circle(mario->GetCollisionRadius(), m_coins[i]->GetCollisionRadius()))
			{
				mario->AddScore(m_coins[i]->GetScoreValue());
				m_coins[i]->Die();
			}
			else if (Collisions::Instance()->Circle(luigi->GetCollisionRadius(), m_coins[i]->GetCollisionRadius()))
			{
				luigi->AddScore(m_coins[i]->GetScoreValue());
				m_coins[i]->Die();
			}

			if (m_coins[i]->GetCollected())
			{
				coinIndexToDelete = i;
			}
		}

		if (coinIndexToDelete != -1)
		{
			m_coins.erase(m_coins.begin() + coinIndexToDelete);
		}
	}
}

void GameScreenLevel1::UpdatePOWBlock(float deltaTime) 
{
	Vector2D marioPos = mario->GetPosition();
	Vector2D marioSize = mario->GetSize();
	int marioGridLocation1[2] = {(int)marioPos.x / TILE_WIDTH, (int)marioPos.y / TILE_HEIGHT};
	int marioGridLocation2[2] = { (int)(marioPos.x + marioSize.x) / TILE_WIDTH, (int)marioPos.y / TILE_HEIGHT };

	Vector2D luigiPos = luigi->GetPosition();
	Vector2D luigiSize = luigi->GetSize();
	int luigiGridLocation1[2] = { (int)luigiPos.x / TILE_WIDTH, (int)luigiPos.y / TILE_HEIGHT };
	int luigiGridLocation2[2] = { (int)(luigiPos.x + luigiSize.x) / TILE_WIDTH, (int)luigiPos.y / TILE_HEIGHT };

	Vector2D POWPos = m_pow_block->GetPosition();
	int POWGridLocation1[2] = { (int)POWPos.x / TILE_WIDTH, ((int)POWPos.y / TILE_HEIGHT) + 1 };
	int POWGridLocation2[2] = { ((int)POWPos.x / TILE_WIDTH) + 1, ((int)POWPos.y / TILE_HEIGHT) + 1 };

	if ((marioGridLocation1[0] == POWGridLocation1[0] && marioGridLocation1[1] == POWGridLocation1[1]) || (marioGridLocation1[0] == POWGridLocation2[0] && marioGridLocation1[1] == POWGridLocation2[1])
		|| (marioGridLocation2[0] == POWGridLocation1[0] && marioGridLocation2[1] == POWGridLocation1[1]) || (marioGridLocation2[0] == POWGridLocation2[0] && marioGridLocation2[1] == POWGridLocation2[1]))
	{

		if (m_pow_block->IsAvailable())
		{
			//collided while jumping
			if (mario->IsJumping())
			{
				DoScreenShake(deltaTime);
				m_pow_block->TakeHit();
				mario->CancelJump();
			}
		}
	}

	if ((luigiGridLocation1[0] == POWGridLocation1[0] && luigiGridLocation1[1] == POWGridLocation1[1]) || (luigiGridLocation1[0] == POWGridLocation2[0] && luigiGridLocation1[1] == POWGridLocation2[1])
		|| (luigiGridLocation2[0] == POWGridLocation1[0] && luigiGridLocation2[1] == POWGridLocation1[1]) || (luigiGridLocation2[0] == POWGridLocation2[0] && luigiGridLocation2[1] == POWGridLocation2[1]))
	{
		if (m_pow_block->IsAvailable())
		{
			//collided while jumping
			if (luigi->IsJumping())
			{
				DoScreenShake(deltaTime);
				m_pow_block->TakeHit();
				luigi->CancelJump();
			}
		}
	}
}

bool GameScreenLevel1::SetUpLevel() 
{
	m_backgroundTexture = new Texture2D(m_renderer);

	if (!m_backgroundTexture->LoadFromFile("Images/Level1.png", SCREEN_WIDTH, SCREEN_HEIGHT)) 
	{
		cout << "Failed to load background texture!\n";
		return false;
	}

	SetLevelMap();

	LoadMusic("Music/MarioUnderworld.mp3");
	if (Mix_PlayingMusic() == 0)
	{
		Mix_PlayMusic(m_music, -1);
	}

	mario = new Mario(m_renderer, "Images/MarioSprites.png", Vector2D(100, SCREEN_HEIGHT - (TILE_HEIGHT * 2) - PLAYER_HEIGHT), FACING_RIGHT, m_level_map);
	luigi = new Luigi(m_renderer, "Images/LuigiSprites.png", Vector2D(SCREEN_WIDTH - 100 - PLAYER_WIDTH, SCREEN_HEIGHT - (TILE_HEIGHT * 2) - PLAYER_HEIGHT), FACING_RIGHT, m_level_map);

	CreateCoin(Vector2D(TILE_WIDTH * 7,TILE_HEIGHT * 4));
	//CreateFly(Vector2D(TILE_WIDTH, 0), FACING_RIGHT);

	m_enemy_wave_time = INITIAL_ENEMY_WAVE_TIME;

	m_pow_block = new PowBlock(m_renderer, m_level_map);

	m_screenshake = false;
	m_background_yPos = 0.0f;

	return true;
}

void GameScreenLevel1::SetLevelMap() 
{
	int map[MAP_HEIGHT][MAP_WIDTH] = { 
					  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
					  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  {0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0 },
					  {1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1 },
					  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  {1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1 },
					  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
					  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
					  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }

	};

	//clear any old maps
	if (m_level_map != nullptr)
	{
		delete m_level_map;
	}

	//set the new one
	m_level_map = new LevelMap(map);
}

void GameScreenLevel1::DoScreenShake(float deltaTime) 
{
	m_screenshake = true;
	m_shake_time = SHAKE_DURATION;
	m_wobble = 0.0f;

	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->TakeDamage(deltaTime);
	}
}
