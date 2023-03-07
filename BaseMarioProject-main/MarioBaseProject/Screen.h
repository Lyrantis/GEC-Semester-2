#pragma once
#include <SDL.h>
#include "Constants.h"

class Screen
{
protected:
	SDL_Renderer* m_renderer;

public:

	Screen();
	Screen(SDL_Renderer* renderer);

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);


};

