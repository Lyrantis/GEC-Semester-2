#include "Character.h"
#pragma once

class Player : public Character
{
	SoundEffect* m_jump_sound;

public:

	Player(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, FACING start_facing, LevelMap* map);
	~Player();

	void Jump(float deltaTime);

	virtual void Update(float deltaTime, SDL_Event e);
	void Render();

	void Die(float deltaTime);

};

