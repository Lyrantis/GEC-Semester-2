#include "Mario.h"
#include "Texture2D.h"

Mario::Mario(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, FACING start_facing, LevelMap* map) : Player(renderer, imagePath, start_position, start_facing, map) {

}

Mario::~Mario()
{

}

void Mario::Update(float deltaTime, SDL_Event e) {

	switch (e.type)
	{

	case SDL_KEYDOWN:

		switch (e.key.keysym.sym) {

		case SDLK_w:

			if (m_can_jump) {

				Player::Jump(deltaTime);
			}
	
			break;

		case SDLK_s:

			
			break;

		case SDLK_a:

			m_direction = FACING_LEFT;
			m_moving = true;
			break;

		case SDLK_d:

			m_direction = FACING_RIGHT;
			m_moving = true;
			break;
		}
		break;

	case SDL_KEYUP:

		switch (e.key.keysym.sym) {

		case SDLK_s:

			break;

		case SDLK_a: case SDLK_d:

			m_moving = false;
			break;

		}

		break;
	}

	Player::Update(deltaTime, e);
}
