#pragma once
#include "Screen.h"
#include <string>

class ScoreScreen : public Screen
{
private:

	bool SetUpScreen();

	Texture2D* m_pointerTexture;
	Rect2D* m_pointerRect;

	TextRenderer* m_nameText;

	TextRenderer* m_highScoreTexts[5];
	TextRenderer* m_highScoreNameTexts[5];

	std::string m_name = "---";
	int currentLetter = 0;
	int m_pointerPos = 0;
	int m_letterWidth = 64;
	char characters[28] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'l', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '.', '-'};

	bool keyStates[7] = { false };
	bool nameEntered = false;
	float timeToChange = 5.0f;

public:

	ScoreScreen(SDL_Renderer* renderer);
	~ScoreScreen();

	bool Update(float deltaTime, SDL_Event e);
	void Render();
};