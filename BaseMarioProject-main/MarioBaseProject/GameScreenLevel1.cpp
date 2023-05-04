#include "GameScreenLevel1.h"
#include <iostream>
#include <fstream>
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

	delete m_marioScoreText;
	m_marioScoreText = nullptr;

	delete m_luigiScoreText;
	m_luigiScoreText = nullptr;
}

void GameScreenLevel1::Render() 
{
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

	m_marioScoreText->Render(150, -6);
	m_luigiScoreText->Render(840, -6);
	m_highScoreText->Render(480, -6);

	m_backgroundTexture->Render(Vector2D(0.0f, m_background_yPos), SDL_FLIP_NONE);
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

	UpdateCoins(deltaTime, e);
	UpdateEnemies(deltaTime, e);
	UpdatePOWBlock(deltaTime);

	if (!mario->GetActive() && !luigi->GetActive())
	{
		return SCREEN_HIGHSCORES;
	}

	if (m_enemies.size() == 0 && m_enemies_to_spawn.size() == 0)
	{
		return SCREEN_HIGHSCORES;
	}

	return SCREEN_NONE;
}

void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e)
{
	if (!m_enemies.empty())
	{
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < m_enemies.size(); i++)
		{

			m_enemies[i]->Update(deltaTime, e);

			//check to see if enemy collides with player
			if (m_enemies[i]->GetAvailable())
			{
				if (Collisions::Instance()->Circle(m_enemies[i]->GetCollisionRadius(), mario->GetCollisionRadius()))
				{

					if (m_enemies[i]->GetInjured())
					{
						if (m_enemies[i]->GetPosition().x > SCREEN_WIDTH / 2)
						{
							std::cout << "Making Coin\n";
							CreateCoin(Vector2D(SCREEN_WIDTH - (m_enemies[i]->GetSize().x), TILE_HEIGHT * 2), FACING_LEFT);
						}
						else
						{
							std::cout << "Making Coin\n";
							CreateCoin(Vector2D(0, TILE_HEIGHT * 2), FACING_RIGHT);
						}

						m_enemies[i]->Die();

						ScoreSystem::Instance()->AddMarioScore(m_enemies[i]->GetScoreValue());
						m_marioScoreText->SetMessage(to_string(ScoreSystem::Instance()->GetMarioScore()));
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

						if (m_enemies[i]->GetPosition().x > SCREEN_WIDTH / 2)
						{
							std::cout << "Making Coin\n";
							CreateCoin(Vector2D(SCREEN_WIDTH - (m_enemies[i]->GetSize().x), TILE_HEIGHT * 2), FACING_LEFT);
						}
						else
						{
							std::cout << "Making Coin\n";
							CreateCoin(Vector2D(0, TILE_HEIGHT * 2), FACING_RIGHT);
						}

						m_enemies[i]->Die();
						ScoreSystem::Instance()->AddLuigiScore(m_enemies[i]->GetScoreValue());
						m_luigiScoreText->SetMessage(to_string(ScoreSystem::Instance()->GetLuigiScore()));
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

		int enemiesSpawned = 0;
		while (m_enemies_to_spawn.size() > 0 && enemiesSpawned < 2)
		{
			string enemyType = m_enemies_to_spawn[0];

			if (enemiesSpawned == 0)
			{
				if (enemyType == "Koopa")
				{
					CreateKoopa(Vector2D(0, TILE_HEIGHT * 2), FACING_RIGHT);
				}
				else if (enemyType == "Fly")
				{
					CreateFly(Vector2D(0, TILE_HEIGHT * 2), FACING_RIGHT);
				}
			}
			else
			{
				if (enemyType == "Koopa")
				{
					CreateKoopa(Vector2D(SCREEN_WIDTH - KOOPA_WIDTH, TILE_HEIGHT * 2), FACING_LEFT);
				}
				else if (enemyType == "Fly")
				{
					CreateFly(Vector2D(SCREEN_WIDTH - FLY_WIDTH, TILE_HEIGHT * 2), FACING_LEFT);
				}
			}

			m_enemies_to_spawn.erase(m_enemies_to_spawn.begin());
			enemiesSpawned++;
		}
	}
}

void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction)
{
	m_enemies.push_back(new Koopa(m_renderer, "Images/ShellCreeper.png", position, direction, m_level_map));
}

void GameScreenLevel1::CreateFly(Vector2D position, FACING direction)
{
	m_enemies.push_back(new FighterFly(m_renderer, "Images/Fighter_Fly.png", position, direction, m_level_map));
}

void GameScreenLevel1::CreateCoin(Vector2D position, FACING facingDirection)
{
	m_coins.push_back(new Coin(m_renderer, "Images/Coin.png", position, facingDirection, m_level_map));
}

void GameScreenLevel1::UpdateCoins(float deltaTime, SDL_Event e)
{

	if (!m_coins.empty())
	{
		int coinIndexToDelete = -1;
		for (int i = 0; i < m_coins.size(); i++)
		{
			m_coins[i]->Update(deltaTime, e);

			if (Collisions::Instance()->Circle(mario->GetCollisionRadius(), m_coins[i]->GetCollisionRadius()))
			{
				ScoreSystem::Instance()->AddMarioScore(m_coins[i]->GetScoreValue());
				m_marioScoreText->SetMessage(to_string(ScoreSystem::Instance()->GetMarioScore()));
				m_coins[i]->Die();
			}
			else if (Collisions::Instance()->Circle(luigi->GetCollisionRadius(), m_coins[i]->GetCollisionRadius()))
			{
				ScoreSystem::Instance()->AddLuigiScore(m_coins[i]->GetScoreValue());
				m_luigiScoreText->SetMessage(to_string(ScoreSystem::Instance()->GetLuigiScore()));
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
	luigi = new Luigi(m_renderer, "Images/LuigiSprites.png", Vector2D(SCREEN_WIDTH - 100 - PLAYER_WIDTH, 10), FACING_RIGHT, m_level_map);

	CreateCoin(Vector2D(TILE_WIDTH * 7,TILE_HEIGHT * 4), FACING_RIGHT);

	m_enemies_to_spawn.push_back("Koopa");
	m_enemies_to_spawn.push_back("Koopa");
	m_enemies_to_spawn.push_back("Koopa");
	m_enemies_to_spawn.push_back("Koopa");
	m_enemies_to_spawn.push_back("Koopa");
	m_enemies_to_spawn.push_back("Koopa");
	m_enemies_to_spawn.push_back("Fly");
	m_enemies_to_spawn.push_back("Fly");
	m_enemies_to_spawn.push_back("Koopa");
	m_enemies_to_spawn.push_back("Koopa");

	m_enemy_wave_time = INITIAL_ENEMY_WAVE_TIME;

	m_pow_block = new PowBlock(m_renderer, m_level_map);

	m_screenshake = false;
	m_background_yPos = 0.0f;

	SDL_Color colour;
	colour.r = 255; colour.g = 255; colour.b = 255; colour.a = 255;

	m_marioScoreText = new TextRenderer(m_renderer);
	m_marioScoreText->LoadFont("Fonts/PixelEmulator.ttf", 32, "0", colour);

	m_luigiScoreText = new TextRenderer(m_renderer);
	m_luigiScoreText->LoadFont("Fonts/PixelEmulator.ttf", 32, "0", colour);

	m_highScoreText = new TextRenderer(m_renderer);
	m_highScoreText->LoadFont("Fonts/PixelEmulator.ttf", 32, ScoreSystem::Instance()->leaderboardScores[0], colour);

	return true;
}

void GameScreenLevel1::SetLevelMap() 
{

	ifstream mapFile;
	mapFile.open("LevelMaps/StandardLevel.txt");
	string currentLine;

	int map[MAP_HEIGHT][MAP_WIDTH];

	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		getline(mapFile, currentLine, '\n');

		for (int j = 0; j < MAP_WIDTH; j++)
		{
			map[i][j] = currentLine[j];
			map[i][j] -= 48;
		}
	}

	mapFile.close();

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
