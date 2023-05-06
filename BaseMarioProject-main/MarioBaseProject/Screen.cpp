#include "Screen.h"
using namespace std;

Screen::Screen(SDL_Renderer* renderer) {

	m_renderer = renderer;

}

Screen::~Screen() {
	m_renderer = nullptr;
	delete m_backgroundTexture;
	m_backgroundTexture = nullptr;
}

void Screen::Render(){};

bool Screen::Update(float deltaTime, SDL_Event e) { return false; };

void Screen::LoadMusic(string path)
{
	m_music = Mix_LoadMUS(path.c_str());

	if (m_music == nullptr)
	{
		cout << "Failed. " << Mix_GetError() << endl;
	}
}

