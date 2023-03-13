#pragma once
#include "Player.h"


class Luigi : public Player
{
public:

	Luigi(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, int imageW, int imageH);

	void Update(float deltaTime, SDL_Event e);
};
