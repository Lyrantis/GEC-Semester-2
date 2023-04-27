#pragma once
#include "Screen.h"

class MainMenuScreen : public Screen
{
private:

	bool SetUpScreen();

public:

	MainMenuScreen(SDL_Renderer* renderer);
	~MainMenuScreen();

	SCREENS Update(float deltaTime, SDL_Event e);
	void Render();
};

