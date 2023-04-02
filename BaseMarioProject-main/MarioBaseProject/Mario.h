#pragma once
#include "Character.h"

class Mario : public Character
{
public:

	Mario(SDL_Renderer* renderer, std::string imagePath, Vector2D imageSize, Vector2D start_position, float movement_speed, Vector2D size, LevelMap* map);

	void Update(float deltaTime, SDL_Event e);
};

