#include "Coin.h"

Coin::Coin(SDL_Renderer* renderer, std::string imagePath, Vector2D position, FACING direction, LevelMap* map) : Character(renderer, imagePath, Vector2D(COIN_SPRITE_WIDTH, COIN_SPRITE_HEIGHT), position, Vector2D(COIN_WIDTH, COIN_HEIGHT), direction, 0.0f, map)
{
	m_score_value = COIN_POINT_VALUE;

	m_current_frame = 0;
	m_frame_delay = COIN_FRAME_DELAY;

	m_death_sound = new SoundEffect("Sounds/Coin.wav");

	m_movement_speed = 100.0f;

	m_moving = true;
}

Coin::~Coin()
{

}

void Coin::Update(float deltaTime, SDL_Event e)
{

	if (m_is_in_level)
	{
		Character::Update(deltaTime, e);

		//is the enemy off screen to the left / right?
		if (m_position.x < 0.0f || m_position.x > SCREEN_WIDTH - (float)(m_size.x))
		{
			//check if the enemy is on the bottom row of tiles
			if (m_position.y < SCREEN_HEIGHT - ((TILE_HEIGHT * 2) + m_size.y))
			{
				FlipDirection();
			}
			else
			{
				m_moving = false;
				m_alive = false;
				m_collected = true;
			}
		}

		m_frame_delay -= deltaTime;
		if (m_frame_delay <= 0.0f)
		{
			//reset frame delay count
			m_frame_delay = COIN_FRAME_DELAY;

			//move the frame over
			m_current_frame++;
			m_sprite_pos.x += m_sprite_size.x;

			//loop frame around if it goes beyond the number of frames
			if (m_current_frame > 2)
			{
				m_current_frame = 0;
				m_sprite_pos.x = 0;
			}
		}
	}
	else
	{
		if (m_direction == FACING_LEFT)
		{
			MoveLeft(deltaTime);
			if (m_position.x <= SCREEN_WIDTH - ((TILE_WIDTH * 4) + m_size.x))
			{
				m_is_in_level = true;
			}
		}
		else if (m_direction == FACING_RIGHT)
		{
			MoveRight(deltaTime);
			if (m_position.x >= TILE_WIDTH * 4)
			{
				m_is_in_level = true;
			}
		}
	}
	
}

void Coin::Die()
{
	Character::Die();
	m_collected = true;
}

