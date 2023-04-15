#pragma once
#include "Player.h"

class Luigi : public Player
{
public:

	Luigi(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, FACING start_facing, LevelMap* map);
	~Luigi();

	void Update(float deltaTime, SDL_Event e);

};
