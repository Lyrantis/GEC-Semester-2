#pragma once
#include <SDL.h>

using namespace std;

class Brick
{
public:
	int x = 0;
	int y = 0;
	int size = 32;
	SDL_Rect location;
	Brick();
	Brick(float xPos, float yPos, float brickSize);

	~Brick();

private:

};

