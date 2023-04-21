#include "Character.h"
#pragma once

class Player : public Character
{
	
	int m_score = 0;

	SoundEffect* m_jump_sound;

public:

	Player(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, FACING start_facing, LevelMap* map);
	~Player();

	void Jump(float deltaTime);

	virtual void Update(float deltaTime, SDL_Event e);
	void Render();

	void Die(float deltaTime);

	int GetScore() { return m_score; }
	void AddScore(int scoreToAdd) { m_score += scoreToAdd; }
};

