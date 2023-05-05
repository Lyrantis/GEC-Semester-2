#include "Player.h"
#include "Texture2D.h"

Player::Player(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, FACING start_facing, LevelMap* map) : Character(renderer, imagePath, Vector2D(PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT), start_position, Vector2D(PLAYER_WIDTH, PLAYER_HEIGHT), start_facing, PLAYER_SPEED, map)
{
	m_jump_force = PLAYER_JUMP_FORCE;
	m_jump_sound = new SoundEffect("Sounds/Jump.wav");
	m_death_sound = new SoundEffect("Sounds/Death.wav");
	m_animation_frame_delay = PLAYER_FRAME_DELAY;
	m_bumpingTime = INITIAL_BUMP_TIME;
}

Player::~Player()
{

}

void Player::Jump(float deltaTime)
{
	m_initial_jump_force = PLAYER_JUMP_FORCE;
	Character::Jump(deltaTime);
	m_jump_sound->Play(0);

}

void Player::Update(float deltaTime, SDL_Event e)
{
	if (m_alive)
	{
		Character::Update(deltaTime, e);

		if (m_is_jumping || m_isBumpingPlatform)
		{
			m_sprite_pos.x = m_sprite_size.x * 6;

			if (m_isBumpingPlatform)
			{
				std::cout << m_bumpingTime << std::endl; 
				m_should_fall = false;
				m_bumpingTime -= deltaTime;

				int leftX_position = (int)(m_position.x + 1) / TILE_WIDTH;
				int rightX_position = (int)(m_position.x + (m_size.x - 1)) / TILE_WIDTH;
				int head_position = (int)(m_position.y) / TILE_HEIGHT;

				if (m_bumpingTime <= 0.0f || (m_current_level_map->GetTileAt(head_position, leftX_position) == 0 && m_current_level_map->GetTileAt(head_position, rightX_position) == 0))
				{
					m_isBumpingPlatform = false;
					m_bumpingTime = INITIAL_BUMP_TIME;
					m_should_fall = true;
				}
			}
		}
		else if (m_moving)
		{
			m_animation_frame_delay -= deltaTime;

			if (m_animation_frame_delay <= 0)
			{
				m_sprite_pos.x += m_sprite_size.x;
				m_animation_frame_delay = PLAYER_FRAME_DELAY;

				if (m_sprite_pos.x >= m_sprite_size.x * 6)
				{
					m_sprite_pos.x = 0;
				}
			}
		}
		else
		{
			if (!m_is_jumping)
			{
				m_animation_frame_delay = PLAYER_FRAME_DELAY;
				m_sprite_pos.x = 0;
			}
		}
	}
	else
	{
		m_animation_frame_delay -= deltaTime;

		if (m_animation_frame_delay <= 0)
		{
			m_sprite_pos.x += m_sprite_size.x;
			m_animation_frame_delay = PLAYER_FRAME_DELAY;

			if (m_sprite_pos.x >= m_sprite_size.x * 6)
			{
				m_sprite_pos.x = m_sprite_size.x * 4;
			}
		}

		m_position.y += GRAVITY_STRENGTH * deltaTime;

		if (m_position.y > SCREEN_HEIGHT)
		{
			m_position = Vector2D(-100, -100);
			m_active = false;
		}
	}
}

void Player::Render()
{
	if (m_direction == FACING_RIGHT)
	{
		m_texture->Render(Rect2D(m_sprite_pos.x, m_sprite_pos.y, m_sprite_size.x, m_sprite_size.y), Rect2D(m_position.x, m_position.y, m_size.x, m_size.y), SDL_FLIP_HORIZONTAL);
	}
	else
	{
		m_texture->Render(Rect2D(m_sprite_pos.x, m_sprite_pos.y, m_sprite_size.x, m_sprite_size.y), Rect2D(m_position.x, m_position.y, m_size.x, m_size.y), SDL_FLIP_NONE);
	}
}
	


void Player::Die(float deltaTime)
{
	Character::Die();
	Character::Jump(deltaTime);
	m_sprite_pos.y = m_sprite_size.y;
	m_isBumpingPlatform = false;
}
