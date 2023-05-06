#include "SideStepper.h"

SideStepper::SideStepper(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, FACING start_facing, LevelMap* map) : Enemy(renderer, imagePath, Vector2D(SIDESTEPPER_SPRITE_WIDTH, SIDESTEPPER_SPRITE_HEIGHT), start_position, Vector2D(SIDESTEPPER_WIDTH, SIDESTEPPER_HEIGHT), start_facing, SIDESTEPPER_SPEED, map )
{
	m_moving = true;
	m_score_value = SIDESTEPPER_SCORE_VALUE;
	m_animation_frame_delay = SIDESTEPPER_FRAME_DELAY;
}

SideStepper::~SideStepper()
{

}

void SideStepper::TakeDamage(float deltaTime)
{
	Enemy::TakeDamage(deltaTime);
	m_mad = true;
}

void SideStepper::Update(float deltaTime, SDL_Event e)
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
				m_animation_frame_delay = SIDESTEPPER_FRAME_DELAY;

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
				
			}
		}
	}
}

void SideStepper::FLipBackUp()
{
}

