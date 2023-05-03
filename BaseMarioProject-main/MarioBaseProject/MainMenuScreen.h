#pragma once
#include "Screen.h"

class MainMenuScreen : public Screen
{
private:

	TextRenderer* m_text;
	std::string m_textMessage = "Welcome! Press space to start!";

	bool SetUpScreen();

public:

	MainMenuScreen(SDL_Renderer* renderer);
	~MainMenuScreen();

	SCREENS Update(float deltaTime, SDL_Event e);
	void Render();
};

