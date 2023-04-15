#include "Luigi.h"
#include "Texture2D.h"

Luigi::Luigi(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, FACING start_facing, LevelMap* map) : Character(renderer, imagePath, Vector2D(PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT), start_position, Vector2D(PLAYER_WIDTH, PLAYER_HEIGHT), start_facing, PLAYER_SPEED, map) {

}

void Luigi::Render()
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