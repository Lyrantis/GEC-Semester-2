#pragma once
#include "game.h"
#include <vector>

class Texture2D;
class PowBlock;

class GameScreenLevel1 : public Screen
{

private:

	LevelMap* m_level_map = nullptr;

	Texture2D* m_bumpedPlatformTexture = nullptr;
	Rect2D* m_mario_bumped_platform_rect = nullptr;

	Texture2D* m_luigi_bumped_platform_texture = nullptr;
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

	void CreateCoin(Vector2D position, FACING facingDirection);
	void UpdateCoins(float deltaTime, SDL_Event e);

public:

	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render() override;
	SCREENS Update(float deltaTime, SDL_Event e) override;
	void UpdatePOWBlock(float deltaTime);
};
