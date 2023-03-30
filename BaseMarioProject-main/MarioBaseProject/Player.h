#pragma once
#include <SDL.h>
#include <iostream>
#include "Constants.h"
#include "LevelMap.h"
#include "Commons.h"
#include <map>

class Texture2D;

class Player
{

protected:

	SDL_Renderer* m_renderer;
	Vector2D m_position;
	FACING m_direction = FACING_RIGHT;
	Texture2D* m_texture;

	Vector2D m_size;
	float m_collision_radius;

public:

	int speed = 5;

	std::map<std::string, bool> keyStates{
		{"w", false},
		{"a", false},
		{"s", false},
		{"d", false},
		{"space", false},
		{"shift", false}
	};

	bool m_grounded = false;

	bool m_can_jump = false;
	bool m_is_jumping = false;
	float m_jump_force = INITIAL_JUMP_FORCE;

	Player();
	Player(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, int imageW, int imageH, LevelMap* map);

	~Player();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	void HandleInputs(float deltaTime);
	void MoveLeft(float deltaTime);
	void MoveRight(float deltaTime);

	void Jump(float deltsTime);
	void AddGravity(float deltaTime);

	void SetPosition(Vector2D new_position);
	Vector2D GetPosition();
	Circle2D GetCollisionRadius();
	Rect2D GetCollisionBox() {
		return Rect2D(m_position.x, m_position.y,
			m_size.x, m_size.y);
	}


private:

	LevelMap* m_current_level_map;
	
};

