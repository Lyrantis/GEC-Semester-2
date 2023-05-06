#include "Enemy.h"
#pragma once

class FighterFly : public Enemy
{
private:

	float m_jump_delay;

public:

	FighterFly(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, FACING start_facing, LevelMap* map);
	~FighterFly();

	void Update(float deltaTime, SDL_Event e);
	void TakeDamage(float deltaTime);

};