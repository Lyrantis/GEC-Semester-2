#include "Luigi.h"
#include "Texture2D.h"

Luigi::Luigi(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, FACING start_facing, LevelMap* map) : Player(renderer, imagePath, start_position, start_facing, map) 
{

}

Luigi::~Luigi()
{

}

void Luigi::Update(float deltaTime, SDL_Event e) {

	switch (e.type)
	{

	case SDL_KEYDOWN:

		switch (e.key.keysym.sym) {
		case SDLK_SPACE:

			break;

		case SDLK_UP:

			if (m_can_jump) {

				Player::Jump(deltaTime);
			}
			
			break;

		case SDLK_LEFT:

			m_moving = true;
			m_direction = FACING_LEFT;
			break;

		case SDLK_RIGHT:

			m_moving = true;
			m_direction = FACING_RIGHT;
			break;
		}
		break;

	case SDL_KEYUP:

		switch (e.key.keysym.sym) {

		case SDLK_LEFT: case SDLK_RIGHT:
			
			m_moving = false;
			break;
		}

		break;

	}

	Player::Update(deltaTime, e);
}