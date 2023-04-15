#include "Screen.h"
using namespace std;

Screen::Screen(SDL_Renderer* renderer) {

	m_renderer = renderer;

}

Screen::Screen() {
	m_renderer = nullptr;
}

void Screen::Render(){};

void Screen::Update(float deltaTime, SDL_Event e){};

void Screen::LoadMusic(string path)
{
	g_music = Mix_LoadMUS(path.c_str());

	if (g_music == nullptr)
	{
		cout << "Failed. " << Mix_GetError() << endl;
	}
}
