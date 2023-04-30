#include "Enemy.h"

Enemy::Enemy(SDL_Renderer* renderer, std::string imagePath, Vector2D imageSize, Vector2D start_position, Vector2D size, FACING start_facing, float movement_speed, LevelMap* map) : Character(renderer, imagePath, imageSize, start_position, size, start_facing, movement_speed, map)
{
	m_initial_jump_force = ENEMY_JUMP_FORCE;
	m_death_sound = new SoundEffect("Sounds/EnemyDefeat.wav");
}

Enemy::~Enemy()
{

}

void Enemy::TakeDamage(float deltaTime)
{
	if (!m_is_jumping)
	{
		m_sprite_pos.x = m_sprite_size.x;
		m_injured = true;
		m_moving = false;
		m_injured_time = INJURED_TIME;
		Character::Jump(deltaTime);
	}
}

void Enemy::Update(float deltaTime, SDL_Event e)
{
	Character::Update(deltaTime, e);

	if(m_injured)
	{
		if (m_is_grounded)
		{
			//count down the injured time
			m_injured_time -= deltaTime;

			if (m_injured_time <= 0.0)
			{
				FlipBackUp(deltaTime);
			}
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

	m_moving = true;
	m_injured = false;
	m_sprite_pos.x = 0;
	Character::Jump(deltaTime);
}