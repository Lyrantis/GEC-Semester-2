#pragma once
#include "game.h"
#include <vector>

class Texture2D;
class PowBlock;

class GameScreenLevel1 : Screen
{

private:
	Texture2D* m_backgroundTexture;
	LevelMap* m_level_map;

	Mario* mario;
	Luigi* luigi;

	vector<Koopa*> m_enemies;

	PowBlock* m_pow_block;

	float m_enemy_wave_time;

	bool m_screenshake;
	float m_shake_time;
	float m_wobble;
	float m_background_yPos;

	bool SetUpLevel();
	void SetLevelMap();
	void DoScreenShake(float deltaTime);

	void UpdateEnemies(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);

public:

	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;
	void UpdatePOWBlock(float deltaTime);
};
