#include "Player.h"

Player::Player() {

	x = 0;
	y = 0;
	size = 64; 
	location = { x, y, size, size };


}

Player::Player(int xPos, int yPos, int playerSize) {

	x = xPos;
	y = yPos;
	size = playerSize;

	location = { x, y, size, size };
}

Player::~Player() {

}
