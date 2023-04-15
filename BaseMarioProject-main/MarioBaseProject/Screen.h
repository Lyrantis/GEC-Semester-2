#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include "Constants.h"
#include <string>
#include <iostream>
#include <vector>
#include "SoundEffect.h"

class Screen
{
protected:
	SDL_Renderer* m_renderer;

	Mix_Music* g_music = nullptr; 

public:

	Screen();
	Screen(SDL_Renderer* renderer);

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	void LoadMusic(std::string path);

};

