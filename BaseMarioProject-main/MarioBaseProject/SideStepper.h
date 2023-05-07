#pragma once
#include "Enemy.h"

class SideStepper : public Enemy
{
public:

	SideStepper(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, FACING start_facing, LevelMap* map);
	~SideStepper();

	void TakeDamage(float deltaTime);
	void Update(float deltaTime, SDL_Event e);
	void FLipBackUp(float deltaTime);

private:

	bool m_mad = false;
};

