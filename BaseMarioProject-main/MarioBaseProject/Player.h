#pragma once
#include <SDL.h>

class Player
{
public:

	int x;
	int y;
	int size;
	SDL_Rect location;
	SDL_Texture* texture;

	Player();
	Player(int xPos, int yPos, int playerSize, SDL_Texture* playerTexture);

	~Player();

private:


};

