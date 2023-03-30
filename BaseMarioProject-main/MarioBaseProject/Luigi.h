#pragma once
#include "Character.h"

class Luigi : public Character
{
public:

	Luigi(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, int imageW, int imageH, LevelMap* map);

	void Update(float deltaTime, SDL_Event e);
};
