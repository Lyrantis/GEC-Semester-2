#pragma once
#include "Character.h"

class Coin : public Character
{
public:

	int m_score_value;

	Coin(SDL_Renderer* renderer, std::string imagePath, Vector2D position, LevelMap* map);
	~Coin();

	void Update(float deltaTime, SDL_Event e);
	void Render();
	int GetScoreValue() { return m_score_value; }

};

