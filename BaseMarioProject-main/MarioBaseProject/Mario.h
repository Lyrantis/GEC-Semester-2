#pragma once
#include "Player.h"
#include "Texture2D.h"

class Mario : public Player
{
public:

	Mario(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, FACING start_facing, LevelMap* map);
	~Mario();

	void Update(float deltaTime, SDL_Event e);

};
