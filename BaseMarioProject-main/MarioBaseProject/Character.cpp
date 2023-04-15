#include "Character.h"
#include "Texture2D.h"

Character::Character(SDL_Renderer* renderer, std::string imagePath, Vector2D imageSize, Vector2D start_position, Vector2D size, FACING start_facing, float movement_speed, LevelMap* map) {

	m_renderer = renderer;
	m_texture = new Texture2D(m_renderer);
	m_sprite_size = imageSize;

	m_position = start_position;
	m_direction = start_facing;
	m_movement_speed = movement_speed;

	m_size = size;

	m_collision_radius = size.x / 2.0f;

	m_current_level_map = map;

	if (!m_texture->LoadFromFile(imagePath, m_sprite_size.x, m_sprite_size.y)) {

		std::cout << "Failed to load character texture!\n";

	}

}

Character::~Character() {

	m_renderer = nullptr;
}

void Character::Render() {

	if (m_direction == FACING_RIGHT)
	{
		m_texture->Render(Rect2D(m_sprite_pos.x, m_sprite_pos.y, m_sprite_size.x, m_sprite_size.y), Rect2D(m_position.x, m_position.y, m_size.x, m_size.y), SDL_FLIP_NONE);
	}
	else
	{
		m_texture->Render(Rect2D(m_sprite_pos.x, m_sprite_pos.y, m_sprite_size.x, m_sprite_size.y), Rect2D(m_position.x, m_position.y, m_size.x, m_size.y), SDL_FLIP_HORIZONTAL);
	}

}

void Character::Update(float deltaTime, SDL_Event e) 
{
	//collision position variables
	int leftX_position = (int)(m_position.x + 1) / TILE_WIDTH;
	int rightX_position = (int)(m_position.x + (m_size.x - 1)) / TILE_WIDTH;
	int foot_position = (int)(m_position.y + (m_size.y)) / TILE_HEIGHT;
	int head_position = (int)(m_position.y) / TILE_HEIGHT;

	//deal with gravity
	if ((m_current_level_map->GetTileAt(foot_position, leftX_position) == 0) && (m_current_level_map->GetTileAt(foot_position, rightX_position) == 0))
	{
		AddGravity(deltaTime);
		m_can_jump = false;
		m_is_grounded = false;
	}
	else if ((m_current_level_map->GetTileAt(foot_position, leftX_position) == 1) || (m_current_level_map->GetTileAt(foot_position, rightX_position) == 1))
	{
		//collided with ground so we can jump again
		m_can_jump = true;
		m_is_grounded = true;
	}
	
	if (m_is_jumping) 
	{
		m_position.y -= m_jump_force * deltaTime;
		m_jump_force -= JUMP_FORCE_DECREMENT * deltaTime;
		
		if ((m_current_level_map->GetTileAt(head_position, leftX_position) == 1) || (m_current_level_map->GetTileAt(head_position, rightX_position) == 1))
		{
			CancelJump();
		}

		if (m_jump_force <= 0.0f) 
		{
			m_is_jumping = false;
		}
	}
}

void Character::HandleInputs(float deltaTime) {

	if (keyStates["w"]) {

		//jump
	}

	if (keyStates["s"]) {

		//crouch
	}

	if (keyStates["a"]) {

		MoveLeft(deltaTime);
	}
	if (keyStates["d"]) {

		MoveRight(deltaTime); 
	}

}

void Character::MoveLeft(float deltaTime) 
{
	m_direction = FACING_LEFT;

	int leftX_position = (int)(m_position.x) / TILE_WIDTH;
	int foot_position = (int)(m_position.y + (m_size.y - 1)) / TILE_HEIGHT;
	int middle_y_position = (int)((m_position.y + (m_size.y / 2)) / TILE_HEIGHT);
	int head_position = (int)(m_position.y) / TILE_HEIGHT;

	if ((m_current_level_map->GetTileAt(foot_position, leftX_position) == 0) && (m_current_level_map->GetTileAt(head_position, leftX_position) == 0) && (m_current_level_map->GetTileAt(middle_y_position, leftX_position) == 0))
	{
		m_position.x -= m_movement_speed * deltaTime;
	}
}

void Character::MoveRight(float deltaTime) 
{
	m_direction = FACING_RIGHT;

	int rightX_position = (int)(m_position.x + m_size.x) / TILE_WIDTH;
	int foot_position = (int)(m_position.y + (m_size.y - 1)) / TILE_HEIGHT;
	int middle_y_position = (int)((m_position.y + (m_size.y / 2)) / TILE_HEIGHT);
	int head_position = (int)(m_position.y) / TILE_HEIGHT;

	if ((m_current_level_map->GetTileAt(foot_position, rightX_position) == 0) && (m_current_level_map->GetTileAt(head_position, rightX_position) == 0) && (m_current_level_map->GetTileAt(middle_y_position, rightX_position) == 0))
	{
		m_position.x += m_movement_speed * deltaTime;
	}
}

void Character::Jump(float deltaTime) 
{
	m_jump_force = m_initial_jump_force;
	m_is_jumping = true;
	m_can_jump = false;
}

void Character::AddGravity(float deltaTime) 
{
	m_position.y += GRAVITY_STRENGTH * deltaTime;

	if (m_position.y >= SCREEN_HEIGHT - m_size.y) 
	{
		m_position.y = SCREEN_HEIGHT - m_size.y;
		m_can_jump = true;
	}
}

void Character::CancelJump() 
{
	m_jump_force = 0;
}

void Character::SetPosition(Vector2D new_position)
{
	m_position = new_position;
}

Vector2D Character::GetPosition() 
{
	return m_position;
}

Circle2D Character::GetCollisionRadius() 
{
	return Circle2D(m_position.x + (m_size.x / 2), m_position.y + (m_size.y / 2), m_collision_radius);
}

void Character::FlipDirection()
{
	if (m_direction == FACING_LEFT)
	{
		m_direction = FACING_RIGHT;
	}
	else
	{
		m_direction = FACING_LEFT;
	}
}
