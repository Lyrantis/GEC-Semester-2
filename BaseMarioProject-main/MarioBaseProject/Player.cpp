#include "Player.h"
#include "Texture2D.h"

Player::Player(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, FACING start_facing, LevelMap* map) : Character(renderer, imagePath, Vector2D(PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT), start_position, Vector2D(PLAYER_WIDTH, PLAYER_HEIGHT), start_facing, PLAYER_SPEED, map)
{
	m_jump_sound = new SoundEffect("Sounds/Jump.wav");
}

Player::~Player()
{

}

void Player::Jump(float deltaTime)
{
	Character::Jump(deltaTime);
	m_jump_sound->Play(0);

}

void Player::Update(float deltaTime, SDL_Event e)
{

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
