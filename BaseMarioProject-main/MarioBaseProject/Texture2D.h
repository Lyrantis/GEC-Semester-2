#pragma once
#include <SDL.h>
#include <iostream>
#include <string>
#include "Commons.h"

#ifndef _TEXTURE2D_H
#define _TEXTURE2D_H

class Texture2D
{
public:

	Texture2D(SDL_Renderer* renderer);
	~Texture2D();

	bool LoadFromFile(std::string path, int width, int height);
	void Free();
	void Render(Vector2D new_position, SDL_RendererFlip flip, double angle = 0.0);

	int GetWidth() { return m_width; }
	int GetHeight() { return  m_height; }

private:

	SDL_Renderer* m_renderer;
	SDL_Texture* m_texture;

	int m_width;
	int m_height;

};

#endif // !_TEXTURE2D_H



