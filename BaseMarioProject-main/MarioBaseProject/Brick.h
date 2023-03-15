#pragma once
#include <SDL.h>
#include <iostream>
#include "Constants.h"
#include "Commons.h"

class Texture2D;

class Brick
{
protected:

	SDL_Renderer* m_renderer;
	Vector2D m_position;
	Texture2D* m_texture;

	Vector2D m_size;

public:

	Brick(SDL_Renderer* renderer, std::string imagePath, Vector2D position, int imageW, int imageH);

	~Brick();

	virtual void Render();

	Vector2D GetPosition();

	Rect2D GetCollisionBox() {
		return Rect2D(m_position.x, m_position.y, m_size.x, m_size.y);
	}

private:

};

