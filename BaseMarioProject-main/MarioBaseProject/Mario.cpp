#include "Mario.h"
#include "Texture2D.h"

Mario::Mario(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, int imageW, int imageH) : Player(renderer, imagePath, start_position, imageW, imageH) {

	m_renderer = renderer;
	m_position = start_position;

	m_texture = new Texture2D(m_renderer);

	m_size = Vector2D(imageW, imageH);

	if (!m_texture->LoadFromFile(imagePath, imageW, imageH)) {

		std::cout << "Failed to load player texture!\n";

	}
}

void Mario::Update(float deltaTime, SDL_Event e) {

	switch (e.type)
	{

	case SDL_KEYDOWN:

		switch (e.key.keysym.sym) {

		case SDLK_w:

			if (m_can_jump) {

				Jump(deltaTime);
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

	if (m_is_jumping) {

		m_position.y -= m_jump_force;
		m_jump_force -= JUMP_FORCE_DECREMENT;

		if (m_jump_force <= 0.0f) {
			m_is_jumping = false;
			m_jump_force = INITIAL_JUMP_FORCE;
		}
	}

	if (!m_grounded) {

		AddGravity(deltaTime);
	}
}
