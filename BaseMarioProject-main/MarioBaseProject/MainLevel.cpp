#include "MainLevel.h"
#include <iostream>
#include <fstream>
#include "Texture2D.h"
#include "PowBlock.h"

using namespace std;

MainLevel::MainLevel(SDL_Renderer* renderer, int levelNum) : Screen(renderer) 
{
	m_level_map = nullptr;
	m_levelNum = levelNum;
	SetUpLevel();

}

MainLevel::~MainLevel() 
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

void MainLevel::Render() 
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

	m_bumpedPlatformTexture->Render(Rect2D(0, 0, 32, 16), *m_mario_bumped_platform_rect, SDL_FLIP_NONE);
	m_bumpedPlatformTexture->Render(Rect2D(0, 0, 32, 16), *m_luigi_bumped_platform_rect, SDL_FLIP_NONE);
}

bool MainLevel::Update(float deltaTime, SDL_Event e) 
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

	if (mario->m_isBumpingPlatform)
	{
		if (m_level_map->GetTileAt((int)(mario->GetPosition().y) / TILE_HEIGHT, (int)(mario->GetPosition().x - TILE_WIDTH) / TILE_WIDTH) && m_level_map->GetTileAt(((int)mario->GetPosition().y) / TILE_HEIGHT, (int)(mario->GetPosition().x - TILE_WIDTH + 100) / TILE_WIDTH))
		{
			m_mario_bumped_platform_rect->x = mario->GetPosition().x - TILE_WIDTH;
			m_mario_bumped_platform_rect->y = mario->GetPosition().y - (2 * TILE_HEIGHT) + 1;
		}
	}
	else {
		m_mario_bumped_platform_rect->x = -100;
		m_mario_bumped_platform_rect->y = -100;
	}
	
	if (luigi->GetActive())
	{
		luigi->Update(deltaTime, e);
	}

	if (luigi->m_isBumpingPlatform)
	{
		if (m_level_map->GetTileAt((int)(luigi->GetPosition().y) / TILE_HEIGHT, (int)(luigi->GetPosition().x - TILE_WIDTH) / TILE_WIDTH) && m_level_map->GetTileAt(((int)luigi->GetPosition().y) / TILE_HEIGHT, (int)(luigi->GetPosition().x - TILE_WIDTH + 100) / TILE_WIDTH))
		{
			m_luigi_bumped_platform_rect->x = luigi->GetPosition().x - TILE_WIDTH;
			m_luigi_bumped_platform_rect->y = luigi->GetPosition().y - (2 * TILE_HEIGHT) + 1;
		}
	}
	else {
		m_luigi_bumped_platform_rect->x = -100;
		m_luigi_bumped_platform_rect->y = -100;
	}

	UpdateCoins(deltaTime, e);
	UpdateEnemies(deltaTime, e);
	UpdatePOWBlock(deltaTime);

	if (!mario->GetActive() && !luigi->GetActive())
	{
		return true;
	}

	if (m_enemies.size() == 0 && m_enemies_to_spawn.size() == 0)
	{
		return true;
	}

	return false;
}

void MainLevel::UpdateEnemies(float deltaTime, SDL_Event e)
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
							CreateCoin(Vector2D(SCREEN_WIDTH - (m_enemies[i]->GetSize().x), TILE_HEIGHT * 2), FACING_LEFT);
						}
						else
						{
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
							CreateCoin(Vector2D(SCREEN_WIDTH - (m_enemies[i]->GetSize().x), TILE_HEIGHT * 2), FACING_LEFT);
						}
						else
						{
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
				if (Collisions::Instance()->Box(m_enemies[i]->GetCollisionBox(), *m_mario_bumped_platform_rect) || (Collisions::Instance()->Box(m_enemies[i]->GetCollisionBox(), *m_luigi_bumped_platform_rect)))
				{
					if (m_enemies[i]->m_i_frames == 0.0f)
					{
						if (m_enemies[i]->GetInjured())
						{
							std::cout << "FlipBack\n";
							m_enemies[i]->FlipBackUp(deltaTime);
						}
						else
						{
							std::cout << "Hit\n";
							m_enemies[i]->TakeDamage(deltaTime);
						}
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

		if (m_enemies_to_spawn.size() > 0)
		{
			string enemyType = m_enemies_to_spawn[0];

			if (sideToSpawn == 0)
			{
				if (enemyType == "Koopa")
				{
					CreateKoopa(Vector2D(0, TILE_HEIGHT * 2), FACING_RIGHT);
				}
				else if (enemyType == "Fly")
				{
					CreateFly(Vector2D(0, TILE_HEIGHT * 2), FACING_RIGHT);
				}
				sideToSpawn--;
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
				sideToSpawn++;
			}

			m_enemies_to_spawn.erase(m_enemies_to_spawn.begin());
		}
	}
}

void MainLevel::CreateKoopa(Vector2D position, FACING direction)
{
	m_enemies.push_back(new Koopa(m_renderer, "Images/ShellCreeper.png", position, direction, m_level_map));
}

void MainLevel::CreateFly(Vector2D position, FACING direction)
{
	m_enemies.push_back(new FighterFly(m_renderer, "Images/Fighter_Fly.png", position, direction, m_level_map));
}

void MainLevel::CreateCoin(Vector2D position, FACING facingDirection)
{
	m_coins.push_back(new Coin(m_renderer, "Images/Coin.png", position, facingDirection, m_level_map));
}

void MainLevel::UpdateCoins(float deltaTime, SDL_Event e)
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

			if ((Collisions::Instance()->Box(m_coins[i]->GetCollisionBox(), *m_mario_bumped_platform_rect) || (Collisions::Instance()->Box(m_coins[i]->GetCollisionBox(), *m_luigi_bumped_platform_rect)) && !m_coins[i]->m_is_jumping))
			{
				m_coins[i]->FlipDirection();
				m_coins[i]->Jump(deltaTime);
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

void MainLevel::UpdatePOWBlock(float deltaTime) 
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

bool MainLevel::SetUpLevel() 
{
	m_backgroundTexture = new Texture2D(m_renderer);

	std::string backgroundPath = "Images/Level" + to_string(m_levelNum) + ".png";

	if (!m_backgroundTexture->LoadFromFile(backgroundPath, SCREEN_WIDTH, SCREEN_HEIGHT)) 
	{
		cout << "Failed to load background texture!\n";
		return false;
	}

	m_bumpedPlatformTexture = new Texture2D(m_renderer);

	std::string bumpedPath = "Images/BumpedPlatform" + to_string(m_levelNum) + ".png";

	if (!m_bumpedPlatformTexture->LoadFromFile(bumpedPath, TILE_HEIGHT * 2, TILE_WIDTH * 4))
	{
		std::cout << "Failed to load Bumped Platform texture!\n";
		return false;
	}

	m_mario_bumped_platform_rect = new Rect2D(-100, -100, TILE_WIDTH * 4, TILE_HEIGHT * 2);
	m_luigi_bumped_platform_rect = new Rect2D(-100, -100, TILE_WIDTH * 4, TILE_HEIGHT * 2);


	SetLevelMap();

	LoadMusic("Music/MarioUnderworld.mp3");
	if (Mix_PlayingMusic() == 0)
	{
		Mix_PlayMusic(m_music, -1);
	}

	mario = new Mario(m_renderer, "Images/MarioSprites.png", Vector2D(100, SCREEN_HEIGHT - (TILE_HEIGHT * 2) - PLAYER_HEIGHT), FACING_RIGHT, m_level_map);
	luigi = new Luigi(m_renderer, "Images/LuigiSprites.png", Vector2D(SCREEN_WIDTH - 100 - PLAYER_WIDTH, SCREEN_HEIGHT - (TILE_HEIGHT * 2) - PLAYER_HEIGHT), FACING_RIGHT, m_level_map);

	if (m_levelNum == 1)
	{
		m_enemies_to_spawn.push_back("Fly");
		m_enemies_to_spawn.push_back("Fly");
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
		m_enemies_to_spawn.push_back("Koopa");
		m_enemies_to_spawn.push_back("Koopa");
	}

	m_enemy_wave_time = INITIAL_ENEMY_WAVE_TIME;

	m_pow_block = new PowBlock(m_renderer, m_level_map);

	m_screenshake = false;
	m_background_yPos = 0.0f;

	SDL_Color colour;
	colour.r = 255; colour.g = 255; colour.b = 255; colour.a = 255;

	m_marioScoreText = new TextRenderer(m_renderer);
	m_marioScoreText->LoadFont("Fonts/PixelEmulator.ttf", 32, to_string(ScoreSystem::Instance()->GetMarioScore()), colour);

	m_luigiScoreText = new TextRenderer(m_renderer);
	m_luigiScoreText->LoadFont("Fonts/PixelEmulator.ttf", 32, to_string(ScoreSystem::Instance()->GetLuigiScore()), colour);

	m_highScoreText = new TextRenderer(m_renderer);
	m_highScoreText->LoadFont("Fonts/PixelEmulator.ttf", 32, ScoreSystem::Instance()->leaderboardScores[0], colour);

	return true;
}

void MainLevel::SetLevelMap() 
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

void MainLevel::DoScreenShake(float deltaTime) 
{
	m_screenshake = true;
	m_shake_time = SHAKE_DURATION;
	m_wobble = 0.0f;

	for (int i = 0; i < m_enemies.size(); i++)
	{
		if (!m_enemies[i]->IsJumping())
		{
			m_enemies[i]->TakeDamage(deltaTime);
		}
	}
}

bool MainLevel::WinOrLose()
{
	if (mario->GetAlive() || luigi->GetAlive())
	{
		return true;
	}

	return false;
}
