#include "Coin.h"

Coin::Coin(SDL_Renderer* renderer, std::string imagePath, Vector2D position, LevelMap* map) : Character(renderer, imagePath, Vector2D(COIN_SPRITE_WIDTH, COIN_SPRITE_HEIGHT), position, Vector2D(COIN_WIDTH, COIN_HEIGHT), FACING_RIGHT, 0.0f, map)
{
	m_score_value = COIN_POINT_VALUE;
}