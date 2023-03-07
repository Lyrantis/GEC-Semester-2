#pragma once
#include<SDL.h>
#include "Commons.h"

class Screen;

class ScreenManager
{
	private:
		SDL_Renderer* m_renderer;
		Screen* m_currentScreen;

	public:

		ScreenManager(SDL_Renderer* renderer, SCREENS startScreen);
		~ScreenManager();

		void Render();
		void Update(float deltaTime, SDL_Event e);

		void ChangeScreen(SCREENS newScreen);

};

