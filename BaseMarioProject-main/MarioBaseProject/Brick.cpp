#include "Brick.h"
#include "Texture2D.h"

Brick::Brick(SDL_Renderer* renderer, std::string imagePath, Vector2D position, int imageW, int imageH) {

	m_renderer = renderer;
	m_position = position;

	m_texture = new Texture2D(m_renderer);

	m_size = Vector2D(imageW, imageH);

	if (!m_texture->LoadFromFile(imagePath, imageW, imageH)) {

		std::cout << "Failed to load brick texture!\n";
	}

}

Brick::~Brick() {

	m_renderer = nullptr;
}

void Brick::Render() {

	m_texture->Render(m_position, SDL_FLIP_NONE);
}

Vector2D Brick::GetPosition() {

	return m_position;
}
