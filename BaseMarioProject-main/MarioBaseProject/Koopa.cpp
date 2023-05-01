#include "Koopa.h"

Koopa::Koopa(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, FACING start_facing, LevelMap* map) : Enemy(renderer, imagePath, Vector2D(KOOPA_SPRITE_WIDTH, KOOPA_SPRITE_HEIGHT), start_position, Vector2D(KOOPA_WIDTH, KOOPA_HEIGHT), start_facing, KOOPA_SPEED, map)
{
	m_injured = false;
	m_moving = true;
	m_sprite_pos.x = 0.0f;

	m_score_value = KOOPA_SCORE_VALUE;

	m_animation_frame_delay = KOOPA_FRAME_DELAY;
}

Koopa::~Koopa() 
{
	
}

void Koopa::Update(float deltaTime, SDL_Event e)
{
	Enemy::Update(deltaTime, e);

	if (m_is_in_level)
	{
		if (m_moving && m_is_grounded)
		{
			m_animation_frame_delay -= deltaTime;
			if (m_animation_frame_delay <= 0.0f)
			{
				//reset frame delay count
				m_animation_frame_delay = KOOPA_FRAME_DELAY;

				//move the frame over
				m_sprite_pos.x += m_sprite_size.x;

				//loop frame around if it goes beyond the number of frames
				if (m_sprite_pos.x > m_sprite_size.x * 4)
				{
					m_sprite_pos.x = 0;
				}
			}
		}
		else if (m_injured && m_is_grounded)
		{
			m_animation_frame_delay -= deltaTime;

			if (m_animation_frame_delay <= 0.0f)
			{
				m_sprite_pos.x += m_sprite_size.x;
				m_animation_frame_delay = INJURED_TIME / 5;
			}
		}
	}
}

void Koopa::TakeDamage(float deltaTime)
{
	Enemy::TakeDamage(deltaTime);

	m_sprite_pos.x = m_sprite_size.x * 9;
	m_animation_frame_delay = m_injured_time / 5;
}


void Koopa::FlipBackUp(float deltaTime)
{
	Enemy::FlipBackUp(deltaTime);
	m_animation_frame_delay = KOOPA_FRAME_DELAY;
}