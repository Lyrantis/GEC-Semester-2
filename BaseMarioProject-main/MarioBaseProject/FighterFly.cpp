#include "FighterFly.h"

FighterFly::FighterFly(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, FACING start_facing, LevelMap* map) : Enemy(renderer, imagePath, Vector2D(FLY_SPRITE_WIDTH, FLY_SPRITE_HEIGHT), start_position, Vector2D(FLY_WIDTH, FLY_HEIGHT), start_facing, FLY_SPEED, map)
{
	m_jump_delay = FLY_JUMP_DELAY;
	m_initial_jump_force = FLY_JUMP_FORCE;

	m_score_value = FLY_SCORE_VALUE;

	m_animation_frame_delay = FLY_FRAME_DELAY;
}

FighterFly::~FighterFly()
{

}

void FighterFly::Update(float deltaTime, SDL_Event e)
{
	Enemy::Update(deltaTime, e);

	if (m_is_in_level)
	{
		if (!m_injured)
		{
			if (m_is_grounded)
			{
				m_moving = false;
				m_jump_delay -= deltaTime;

				if (m_jump_delay <= 0)
				{
					m_moving = true;
					m_jump_delay = FLY_JUMP_DELAY;
					Character::Jump(deltaTime);
				}
			}
			else if (m_is_jumping)
			{
				m_moving = true;
			}
		}
	}
}