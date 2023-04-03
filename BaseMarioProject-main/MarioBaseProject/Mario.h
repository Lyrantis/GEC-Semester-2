#pragma once
#include "Character.h"

class Mario : public Character
{
public:

	Mario(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, FACING start_facing, LevelMap* map);

	void Update(float deltaTime, SDL_Event e);
};

