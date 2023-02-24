#include "Brick.h"

Brick::Brick() {

	x = 0;
	y = 0;
	size = 32;

}

Brick::Brick(float xPos, float yPos, float brickSize, SDL_Texture* brickTexture) {

	x = xPos;
	y = yPos;
	size = brickSize;
	texture = brickTexture;
	location = { x, y, size, size };

}

Brick::~Brick() {

}