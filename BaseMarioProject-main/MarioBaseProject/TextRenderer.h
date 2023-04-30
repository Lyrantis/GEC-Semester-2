#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <iostream>

class TextRenderer
{
private:

	SDL_Renderer* m_renderer;
	SDL_Texture* m_texture;
	SDL_Rect m_textRect;
	TTF_Font* m_font;
	SDL_Color m_colour;

	std::string m_message; 
	int m_fontSize;

public:

	TextRenderer(SDL_Renderer* renderer);
	~TextRenderer();

	void Render(int x, int y);

	bool LoadFont(const std::string filePath, int fontSize, const std::string message, SDL_Color colour);

	bool SetMessage(std::string newMessage);
};

