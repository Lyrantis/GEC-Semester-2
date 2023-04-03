#pragma once
#include "Character.h"

class Koopa : public Character
{

private:

	float m_injured_time = 0.0f;

	void FlipBackUp(float deltaTime);

public:

	Koopa(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, FACING start_facing, LevelMap* map);
	~Koopa();

	void TakeDamage(float deltaTime);
	void Update(float deltaTime, SDL_Event e);
};

