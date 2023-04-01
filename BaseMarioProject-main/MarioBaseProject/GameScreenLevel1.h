#pragma once
#include "game.h"

class Texture2D;
class PowBlock;

class GameScreenLevel1 : Screen
{

private:
	Texture2D* m_backgroundTexture;
	LevelMap* m_level_map;

	Mario* mario;
	Luigi* luigi;

	PowBlock* m_pow_block;

	bool m_screenshake;
	float m_shake_time;
	float m_wobble;
	float m_background_yPos;


	bool SetUpLevel();
	void SetLevelMap();
	void DoScreenShake();

public:

	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;
	void UpdatePOWBlock();
};
