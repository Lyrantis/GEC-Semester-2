#include "Character.h"
#pragma once

class Enemy : public Character
{
private:

	float m_injured_time = 0.0f;

public:

	Enemy(SDL_Renderer* renderer, std::string imagePath, Vector2D imageSize, Vector2D start_position, Vector2D size, FACING start_facing, float movement_speed, LevelMap* map);
	~Enemy();

	virtual void TakeDamage(float deltaTime);
	virtual void Update(float deltaTime, SDL_Event e);
	void FlipBackUp(float deltaTime);
};
