#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include "Constants.h"
#include <string>
#include <iostream>
#include <vector>
#include "SoundEffect.h"
#include "Texture2D.h"
#include "TextRenderer.h"

class Screen
{
private:

protected:
	SDL_Renderer* m_renderer; 

public:

	Mix_Music* m_music = nullptr;
	Texture2D* m_backgroundTexture;

	
	Screen(SDL_Renderer* renderer);
	~Screen();

	virtual void Render();
	virtual SCREENS Update(float deltaTime, SDL_Event e);

	void LoadMusic(std::string path);

};

