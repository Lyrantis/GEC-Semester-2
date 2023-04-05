#include "Enemy.h"

Enemy::Enemy(SDL_Renderer* renderer, std::string imagePath, Vector2D imageSize, Vector2D start_position, Vector2D size, FACING start_facing, float movement_speed, LevelMap* map) : Character(renderer, imagePath, imageSize, start_position, size, start_facing, movement_speed, map)
{

}

Enemy::~Enemy()
{

}

void Enemy::TakeDamage(float deltaTime)
{

}

void Enemy::Update(float deltaTime, SDL_Event e)
{

}