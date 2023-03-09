#include "Player.h"
#include "Texture2D.h"


Player::Player() {
	
}
Player::Player(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position) {

	m_renderer = renderer;
	m_position = start_position;

	m_texture = new Texture2D(m_renderer);

	if (!m_texture->LoadFromFile(imagePath, 64, 64)) {

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


		switch (e.type)
		{

		case SDL_KEYDOWN:

			switch (e.key.keysym.sym) {
			case SDLK_SPACE:

				//jump
				break;

			case SDLK_w:

				m_position.y -= speed;
				break;

			case SDLK_s:

				m_position.y += speed;
				break;

			case SDLK_a:
				m_direction = FACING_LEFT;
				m_position.x -= speed;
				break;

			case SDLK_d:
				m_direction = FACING_RIGHT;
				m_position.x += speed;
				break;
			}
			break;

		}

	

}

void Player::SetPosition(Vector2D new_position) {

	m_position = new_position;
}

Vector2D Player::GetPosition() {

	return m_position;
}
