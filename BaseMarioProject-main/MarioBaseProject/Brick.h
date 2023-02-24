#pragma once
#include <SDL.h>

using namespace std;

class Brick
{
public:
	int x = 0;
	int y = 0;
	int size = 32;
	SDL_Texture* texture;
	SDL_Rect location;
	Brick();
	Brick(float xPos, float yPos, float brickSize, SDL_Texture* brickTexture);

	~Brick();

private:

};

