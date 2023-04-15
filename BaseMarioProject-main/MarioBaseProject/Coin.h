#pragma once
#include "Character.h"

class Coin : public Character
{
private:

	int m_score_value;
	bool m_collected = false;

	int m_current_frame;
	float m_frame_delay;

public:

	Coin(SDL_Renderer* renderer, std::string imagePath, Vector2D position, LevelMap* map);
	~Coin();

	void Update(float deltaTime);

	void Die();

	int GetScoreValue() { return m_score_value; }

	bool GetCollected() { return m_collected; }

};

