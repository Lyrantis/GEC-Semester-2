#include "Character.h"
#include "Texture2D.h"


Character::Character() {
	
}
Character::Character(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, int imageW, int imageH, LevelMap* map) {

	m_renderer = renderer;
	m_position = start_position;

	m_texture = new Texture2D(m_renderer);

	m_size = Vector2D(imageW, imageH);

	m_collision_radius = 16.0f;

	m_current_level_map = map;

	if (!m_texture->LoadFromFile(imagePath, imageW, imageH)) {

		std::cout << "Failed to load player texture!\n";

	}

}

Character::~Character() {

	m_renderer = nullptr;
}

void Character::Render() {

	if (m_direction == FACING_RIGHT)
	{
		m_texture->Render(m_position, SDL_FLIP_NONE);
	}
	else
	{
		m_texture->Render(m_position, SDL_FLIP_HORIZONTAL);
	}

}

void Character::Update(float deltaTime, SDL_Event e) {

	//collision position variables
	int centralX_position = (int)(m_position.x + (m_texture->GetWidth() * 0.5)) / TILE_WIDTH;
	int foot_position = (int)(m_position.y + m_texture->GetHeight()) / TILE_HEIGHT;
	int head_position = (int)(m_position.y) / TILE_HEIGHT;

	//deal with gravity
	if (m_current_level_map->GetTileAt(foot_position, centralX_position) == 0)
	{
		AddGravity(deltaTime);
	}
	else
	{
		//collided with ground so we can jump again
		m_can_jump = true;
	}
	
	if (m_is_jumping) {

		m_position.y -= m_jump_force * deltaTime;
		m_jump_force -= JUMP_FORCE_DECREMENT * deltaTime;
		
		if (head_position != foot_position && m_current_level_map->GetTileAt(head_position, centralX_position))
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
	m_position.x -= speed * deltaTime;
}

void Character::MoveRight(float deltaTime) 
{
	m_direction = FACING_RIGHT;
	m_position.x += speed * deltaTime;
}

void Character::Jump(float deltaTime) 
{
	m_jump_force = INITIAL_JUMP_FORCE;
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
	return Circle2D(m_position.x, m_position.y, m_collision_radius);
}
