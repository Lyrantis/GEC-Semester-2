#include "Player.h"

Player::Player() {

	x = 0;
	y = 0;
	size = 64; 
	location = { x, y, size, size };

	texture = nullptr;

}

Player::Player(int xPos, int yPos, int playerSize, SDL_Texture* playerTexture) {

	x = xPos;
	y = yPos;
	size = playerSize;
	texture = playerTexture;

	location = { x, y, size, size };
}
