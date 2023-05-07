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

	if (m_i_frames <= 0.0f)
	{

		if (m_mad)
		{
			m_sprite_pos.x = m_sprite_size.x * 5;
			m_animation_frame_delay = INJURED_FRAME_DELAY;
			Enemy::TakeDamage(deltaTime);
		}
		else
		{
			m_mad = true;
			m_sprite_pos.x = m_sprite_size.x * 2;
			m_movement_speed *= SIDESTEPPER_ANGRY_SPEED_MODIFIER;
			m_i_frames = ENEMY_IFRAMES;
		}
	}
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

				if (m_mad)
				{
					//loop frame around if it goes beyond the number of frames
					if (m_sprite_pos.x > m_sprite_size.x * 3)
					{
						m_sprite_pos.x = m_sprite_size.x * 2;
					}
				}
				else
				{
					//loop frame around if it goes beyond the number of frames
					if (m_sprite_pos.x > m_sprite_size.x)
					{
						m_sprite_pos.x = 0;
					}
				}

				
			}
		}
		else if (m_injured && m_is_grounded)
		{
			m_animation_frame_delay -= deltaTime;

			if (m_animation_frame_delay <= 0.0f)
			{
				m_animation_frame_delay = INJURED_FRAME_DELAY;
				m_sprite_pos.x += m_sprite_size.x;
				
				if (m_sprite_pos.x > m_sprite_size.x * 6)
				{
					m_sprite_pos.x = m_sprite_size.x * 5;
				}
			}
		}
	}
}

void SideStepper::FLipBackUp(float deltaTime)
{
	m_mad = false;
	m_movement_speed = SIDESTEPPER_SPEED;
	Enemy::FlipBackUp(deltaTime);
}

