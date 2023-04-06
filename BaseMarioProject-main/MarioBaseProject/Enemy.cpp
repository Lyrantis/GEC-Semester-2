#include "Enemy.h"

Enemy::Enemy(SDL_Renderer* renderer, std::string imagePath, Vector2D imageSize, Vector2D start_position, Vector2D size, FACING start_facing, float movement_speed, LevelMap* map) : Character(renderer, imagePath, imageSize, start_position, size, start_facing, movement_speed, map)
{

}

Enemy::~Enemy()
{

}

void Enemy::TakeDamage(float deltaTime)
{
	m_sprite_pos.x = m_sprite_size.x;
	m_injured = true;
	m_injured_time = INJURED_TIME;
	Character::Jump(deltaTime);
}

void Enemy::Update(float deltaTime, SDL_Event e)
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

void Enemy::FlipBackUp(float deltaTime)
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