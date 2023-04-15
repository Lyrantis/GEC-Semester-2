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

	Character::Update(deltaTime, e);
}
