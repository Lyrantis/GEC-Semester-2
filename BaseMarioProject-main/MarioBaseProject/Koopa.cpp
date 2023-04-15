#include "Koopa.h"

Koopa::Koopa(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, FACING start_facing, LevelMap* map) : Enemy(renderer, imagePath, Vector2D(KOOPA_SPRITE_WIDTH, KOOPA_SPRITE_HEIGHT), start_position, Vector2D(KOOPA_WIDTH, KOOPA_HEIGHT), start_facing, KOOPA_SPEED, map)
{
	m_injured = false;
	m_sprite_pos.x = 0.0f;

	m_score_value = KOOPA_SCORE_VALUE;
}

Koopa::~Koopa() 
{
	
}

void Koopa::Update(float deltaTime, SDL_Event e)
{
	Enemy::Update(deltaTime, e);

	if (!m_injured)
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
