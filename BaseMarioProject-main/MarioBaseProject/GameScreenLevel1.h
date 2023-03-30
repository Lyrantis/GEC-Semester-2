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

	bool SetUpLevel();
	void SetLevelMap();

public:

	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;
	void UpdatePOWBlock();
};
