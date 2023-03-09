#pragma once
#include <SDL.h>
#include <iostream>
#include "Commons.h"

class Texture2D;

class Player
{

protected:

	SDL_Renderer* m_renderer;
	Vector2D m_position;
	FACING m_direction = FACING_RIGHT;
	Texture2D* m_texture;

public:

	SDL_Rect location;
	int speed = 5;

	Player();
	Player(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position);

	~Player();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	void SetPosition(Vector2D new_position);
	Vector2D GetPosition();

private:
	int x;
	int y;
	int size;

};

