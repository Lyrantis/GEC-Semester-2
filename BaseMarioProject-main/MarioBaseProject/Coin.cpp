#include "Coin.h"

Coin::Coin(SDL_Renderer* renderer, std::string imagePath, Vector2D position, LevelMap* map) : Character(renderer, imagePath, Vector2D(COIN_SPRITE_WIDTH, COIN_SPRITE_HEIGHT), position, Vector2D(COIN_WIDTH, COIN_HEIGHT), FACING_RIGHT, 0.0f, map)
{
	m_score_value = COIN_POINT_VALUE;

	m_current_frame = 0;
	m_frame_delay = COIN_FRAME_DELAY;
}

Coin::~Coin()
{

}

void Coin::Update(float deltaTime)
{
	m_frame_delay -= deltaTime;
	if (m_frame_delay <= 0.0f)
	{
		//reset frame delay count
		m_frame_delay = COIN_FRAME_DELAY;

		//move the frame over
		m_current_frame++;
		m_sprite_pos.x += m_sprite_size.x;

		//loop frame around if it goes beyond the number of frames
		if (m_current_frame > 2)
		{
			m_current_frame = 0;
			m_sprite_pos.x = 0;
		}
	}
}

int Coin::GetScoreValue()
{
	if (!m_collected)
	{
		m_collected = true;
		return m_score_value;
	}
	
	return 0;
}
