#pragma once
#include "Screen.h"
#include "Commons.h"

class Texture2D;

class GameScreenLevel1 : Screen
{

private:
	Texture2D* m_backgroundTexture;

	bool SetUpLevel();

public:

	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;

};
