#include "FighterFly.h"

FighterFly::FighterFly(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, FACING start_facing, LevelMap* map) : Enemy(renderer, imagePath, Vector2D(FLY_SPRITE_WIDTH, FLY_SPRITE_HEIGHT), start_position, Vector2D(FLY_WIDTH, FLY_HEIGHT), start_facing, FLY_SPEED, map)
{
	m_jump_delay = FLY_JUMP_DELAY;
}

FighterFly::~FighterFly()
{

}

void FighterFly::Update(float deltaTime, SDL_Event e)
{
	Enemy::Update(deltaTime, e);

	if (!m_injured && m_is_jumping)
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
}