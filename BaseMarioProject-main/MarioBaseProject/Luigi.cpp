#include "Luigi.h"
#include "Texture2D.h"

Luigi::Luigi(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, FACING start_facing, LevelMap* map) : Character(renderer, imagePath, Vector2D(PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT), start_position, Vector2D(PLAYER_WIDTH, PLAYER_HEIGHT), start_facing, PLAYER_SPEED, map) {

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

				Jump(deltaTime);
			}
			
			break;

		case SDLK_DOWN:

			keyStates["s"] = true;
			break;

		case SDLK_LEFT:

			keyStates["a"] = true;
			break;

		case SDLK_RIGHT:

			keyStates["d"] = true;
			break;
		}
		break;

	case SDL_KEYUP:

		switch (e.key.keysym.sym) {
		case SDLK_SPACE:

			//jump
			break;

		case SDLK_UP:

			keyStates["w"] = false;
			break;

		case SDLK_DOWN:

			keyStates["s"] = false;
			break;

		case SDLK_LEFT:

			keyStates["a"] = false;
			break;

		case SDLK_RIGHT:

			keyStates["d"] = false;
			break;

		}

		break;

	}

	HandleInputs(deltaTime);

	Character::Update(deltaTime, e);
}