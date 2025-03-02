#pragma once
#include "game.h"
#include "Character.h"
#include "Mario.h"
#include "Luigi.h"
#include "Koopa.h"
#include "FighterFly.h"
#include "SideStepper.h"
#include "Coin.h"
#include "Collisions.h"
#include "Screen.h"
#include <vector>

class Texture2D;
class PowBlock;

class MainLevel : public Screen
{

private:

	int m_levelNum;

	LevelMap* m_level_map = nullptr;

	Texture2D* m_bumpedPlatformTexture = nullptr;

	Rect2D* m_mario_bumped_platform_rect = nullptr;
	Rect2D* m_luigi_bumped_platform_rect = nullptr;

	Mario* mario = nullptr;
	Luigi* luigi = nullptr;

	vector<std::string> m_enemies_to_spawn;

	vector<Enemy*> m_enemies;
	vector<Coin*> m_coins;

	PowBlock* m_pow_block = nullptr;

	SoundEffect* m_player_spawn_sound = nullptr;
	SoundEffect* m_enemy_spawn_sound = nullptr;

	TextRenderer* m_marioScoreText = nullptr;
	TextRenderer* m_luigiScoreText = nullptr;
	TextRenderer* m_highScoreText = nullptr;

	float m_enemy_wave_time;
	int sideToSpawn = 0;

	bool m_screenshake;
	float m_shake_time;
	float m_wobble;
	float m_background_yPos;

	bool SetUpLevel();
	void SetLevelMap();
	void DoScreenShake(float deltaTime);

	void UpdateEnemies(float deltaTime, SDL_Event e);

	void CreateKoopa(Vector2D position, FACING direction);
	void CreateFly(Vector2D position, FACING direction);
	void CreateSideStepper(Vector2D position, FACING direction);

	void CreateCoin(Vector2D position, FACING facingDirection);
	void UpdateCoins(float deltaTime, SDL_Event e);

	bool WinOrLose();

public:

	MainLevel(SDL_Renderer* renderer, int levelNum = 1);
	~MainLevel();

	void Render() override;
	bool Update(float deltaTime, SDL_Event e) override;
	void UpdatePOWBlock(float deltaTime);
};
