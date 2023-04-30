#include "TextRenderer.h"

TextRenderer::TextRenderer(SDL_Renderer* renderer)
{
	m_renderer = renderer;
}

TextRenderer::~TextRenderer()
{
	m_renderer = nullptr;
	TTF_CloseFont(m_font);
}

void TextRenderer::Render(int x, int y)
{
	m_textRect.x = x; m_textRect.y = y;

	SDL_RenderCopy(m_renderer, m_texture, nullptr, &m_textRect);
}

bool TextRenderer::LoadFont(const std::string filePath, int fontSize, const std::string message, SDL_Color colour)
{
	m_font = TTF_OpenFont(filePath.c_str(), fontSize);
	m_message = message;
	m_colour = colour;
	m_fontSize = fontSize;

	if (!m_font)
	{
		std::cout << "Failed to load font " << filePath << std::endl;
		return false;
	}

	SDL_Surface* textSurface = TTF_RenderText_Solid(m_font, m_message.c_str(), colour);

	if (!textSurface)
	{
		std::cout << "Failed to create texture surface.\n";
		return false;
	}

	m_texture = SDL_CreateTextureFromSurface(m_renderer, textSurface);

	if (!m_texture)
	{
		std::cout << "Failed to create texture.\n";
		return false;
	}

	
	SDL_FreeSurface(textSurface);

	SDL_QueryTexture(m_texture, nullptr, nullptr, &m_textRect.w, &m_textRect.h);

	return m_texture;
}

bool TextRenderer::SetMessage(std::string newMessage)
{
	m_message = newMessage;

	SDL_Surface* textSurface = TTF_RenderText_Solid(m_font, m_message.c_str(), m_colour);

	if (!textSurface)
	{
		std::cout << "Failed to create texture surface.\n";
		return false;
	}

	m_texture = SDL_CreateTextureFromSurface(m_renderer, textSurface);

	if (!m_texture)
	{
		std::cout << "Failed to create texture.\n";
		return false;
	}


	SDL_FreeSurface(textSurface);

	SDL_QueryTexture(m_texture, nullptr, nullptr, &m_textRect.w, &m_textRect.h);
}
