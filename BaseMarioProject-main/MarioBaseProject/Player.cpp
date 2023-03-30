#include "Player.h"
#include "Texture2D.h"


Player::Player() {
	
}
Player::Player(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, int imageW, int imageH, LevelMap* map) {

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

Player::~Player() {

	m_renderer = nullptr;
}

void Player::Render() {

	if (m_direction == FACING_RIGHT)
	{
		m_texture->Render(m_position, SDL_FLIP_NONE);
	}
	else
	{
		m_texture->Render(m_position, SDL_FLIP_HORIZONTAL);
	}

}

void Player::Update(float deltaTime, SDL_Event e) {

	//collision position variables
	int centralX_position = (int)(m_position.x + (m_texture->GetWidth() * 0.5)) / TILE_WIDTH;
	int foot_position = (int)(m_position.y + m_texture->GetHeight()) / TILE_HEIGHT;

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

	switch (e.type)
	{

	case SDL_KEYDOWN:

		switch (e.key.keysym.sym) {
		case SDLK_SPACE:

			if (m_can_jump) {

				Jump(deltaTime);
			}
			break;

		case SDLK_w:

			keyStates["w"] = true;
			break;

		case SDLK_s:

			keyStates["s"] = true;
			break;

		case SDLK_a:
			
			keyStates["a"] = true;
			break;

		case SDLK_d:
			
			keyStates["d"] = true;
			break;
		}
		break;

	case SDL_KEYUP:

		switch (e.key.keysym.sym) {
		case SDLK_SPACE:

			//jump
			break;

		case SDLK_w:

			keyStates["w"] = false;
			break;

		case SDLK_s:

			keyStates["s"] = false;
			break;

		case SDLK_a:

			keyStates["a"] = false;
			break;

		case SDLK_d:

			keyStates["d"] = false;
			break;

		}

		break;

	}
		
	HandleInputs(deltaTime);

	if (m_is_jumping) {

		m_position.y -= m_jump_force;
		m_jump_force -= JUMP_FORCE_DECREMENT;

		if (m_jump_force <= 0.0f) {
			m_is_jumping = false;
			m_jump_force = INITIAL_JUMP_FORCE;
		}
	}

}

void Player::HandleInputs(float deltaTime) {

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

void Player::MoveLeft(float deltaTime) {
	
	m_direction = FACING_LEFT; 
	m_position.x -= speed;
}

void Player::MoveRight(float deltaTime) {

	m_direction = FACING_RIGHT;
	m_position.x += speed;
}

void Player::Jump(float deltaTime) {

	m_grounded = false;
	m_is_jumping = true;
	m_can_jump = false;
}

void Player::AddGravity(float deltaTime) {

	m_position.y += GRAVITY_STRENGTH;

	if (m_position.y >= SCREEN_HEIGHT - m_size.y) {

		m_position.y = SCREEN_HEIGHT - m_size.y;
		m_grounded = true;
		m_can_jump = true;
	}
}

void Player::SetPosition(Vector2D new_position) {

	m_position = new_position;
}

Vector2D Player::GetPosition() {

	return m_position;
}

Circle2D Player::GetCollisionRadius() {

	return Circle2D(m_position.x, m_position.y, m_collision_radius);
}
