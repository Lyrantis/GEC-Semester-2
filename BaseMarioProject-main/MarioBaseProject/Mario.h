#pragma once
#include "Character.h"

class Mario : public Character
{
public:

	int m_score = 0;

	Mario(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, FACING start_facing, LevelMap* map);

	void Render();
	void Update(float deltaTime, SDL_Event e);
	void AddScore(int scoreToAdd) { m_score += scoreToAdd; }
};
