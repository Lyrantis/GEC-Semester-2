#pragma once
#include<SDL.h>
#include "Commons.h"

class Screen;

class ScreenManager
{
	private:
		SDL_Renderer* m_renderer;
		Screen* m_currentScreen;

		int m_currentlevel = 0;
		int m_levelCount = 5;

	public:

		ScreenManager(SDL_Renderer* renderer, int startScreen);
		~ScreenManager();

		void Render();
		void Update(float deltaTime, SDL_Event e);

		void ChangeScreen();

};

