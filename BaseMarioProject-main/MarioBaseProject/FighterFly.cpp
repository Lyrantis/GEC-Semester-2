#include "FighterFly.h"

FighterFly::FighterFly(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, FACING start_facing, LevelMap* map) : Enemy(renderer, imagePath, Vector2D(FLY_SPRITE_WIDTH, FLY_SPRITE_HEIGHT), start_position, Vector2D(FLY_WIDTH, FLY_HEIGHT), start_facing, FLY_SPEED, map)
{
	m_jump_delay = FLY_JUMP_DELAY;
	m_initial_jump_force = FLY_JUMP_FORCE;
}

FighterFly::~FighterFly()
{

}

void FighterFly::Update(float deltaTime, SDL_Event e)
{
	Enemy::Update(deltaTime, e);
	if (!m_injured)
	{
		if (!m_is_grounded)
		{
			//enemy is not injured so move
			if (m_direction == FACING_LEFT)
			{
				Character::MoveLeft(deltaTime);
			}
			else if (m_direction == FACING_RIGHT)
			{
				Character::MoveRight(deltaTime);
			}
		}
		else
		{
			m_jump_delay -= deltaTime;

			if (m_jump_delay <= 0)
			{
				Character::Jump(deltaTime);
				m_jump_delay = FLY_JUMP_DELAY;
			}
		}
	}
}