#include "Koopa.h"

Koopa::Koopa(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, FACING start_facing, LevelMap* map) : Character(renderer, imagePath, Vector2D(KOOPA_SPRITE_WIDTH, KOOPA_SPRITE_HEIGHT), start_position, Vector2D(KOOPA_WIDTH, KOOPA_HEIGHT), start_facing, KOOPA_SPEED, map)
{
	m_injured = false;
	m_sprite_pos.x = 0.0f;
}

Koopa::~Koopa() 
{
	
}

void Koopa::TakeDamage(float deltaTime) 
{
	m_injured = true;
	m_sprite_pos.x = KOOPA_SPRITE_WIDTH;
	m_injured_time = INJURED_TIME;

	Character::Jump(deltaTime);
}

void Koopa::FlipBackUp(float deltaTime) 
{
	if (m_direction == FACING_LEFT) 
	{
		m_direction = FACING_RIGHT;
	}
	else
	{
		m_direction = FACING_LEFT;
	}

	m_injured = false;
	m_sprite_pos.x = 0;
	Character::Jump(deltaTime);
}

void Koopa::Update(float deltaTime, SDL_Event e)
{
	Character::Update(deltaTime, e);

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
	else
	{
		//count down the injured time
		m_injured_time -= deltaTime;

		if (m_injured_time <= 0.0)
		{
			FlipBackUp(deltaTime);
		}	
	}
}