#pragma once
#include <SDL.h>

class Player
{
public:

	SDL_Rect location;
	int speed = 5;

	Player();
	Player(int xPos, int yPos, int playerSize);

	~Player();

private:
	int x;
	int y;
	int size;

};

