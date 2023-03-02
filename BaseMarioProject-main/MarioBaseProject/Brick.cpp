#include "Brick.h"

Brick::Brick() {

	x = 0;
	y = 0;
	size = 32;

}

Brick::Brick(float xPos, float yPos, float brickSize) {

	x = xPos;
	y = yPos;
	size = brickSize;
	location = { x, y, size, size };

}

Brick::~Brick() {


}