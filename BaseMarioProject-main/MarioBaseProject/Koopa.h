#pragma once
#include "Character.h"

class Koopa : public Character
{

private:

	float m_single_sprite_w;
	float single_sprite_h;

	bool m_injured;
	float m_injured_time;

	//void FlipBackRound();

public:

	Koopa(SDL_Renderer* renderer, std::string imagePath, LevelMap* map, Vector2D start_position, FACING start_facing, float movement_speed);
	//~Koopa();

	//void TakeDamage();
	//void Jump();
	//void Update(float deltaTime, SDL_Event e);

};

