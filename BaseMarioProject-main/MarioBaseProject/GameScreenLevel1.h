#pragma once
#include "game.h"


class Texture2D;

class GameScreenLevel1 : Screen
{

private:
	Texture2D* m_backgroundTexture;
	LevelMap* m_level_map;

	Mario* mario;
	Luigi* luigi;

	bool SetUpLevel();
	void SetLevelMap();

public:

	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;

};
