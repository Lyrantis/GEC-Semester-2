#pragma once
#include <SDL.h>
#include <iostream>
#include "Constants.h"
#include "LevelMap.h"
#include "Commons.h"
#include <map>

class Texture2D;

class Character
{

private:

	LevelMap* m_current_level_map;

protected:

	SDL_Renderer* m_renderer;
	Vector2D m_position;
	FACING m_direction = FACING_RIGHT;
	Texture2D* m_texture;
	Vector2D m_sprite_pos = { 0.0f, 0.0f };
	Vector2D m_sprite_size;

	Vector2D m_size;
	float m_collision_radius;

	bool m_alive = true;
	bool m_injured = false;

public:

	float m_movement_speed;

	std::map<std::string, bool> keyStates{
		{"w", false},
		{"a", false},
		{"s", false},
		{"d", false},
		{"space", false},
		{"shift", false}
	};

	bool m_can_jump = false;
	bool m_is_jumping = false;
	float m_jump_force = INITIAL_JUMP_FORCE;

	Character(SDL_Renderer* renderer, std::string imagePath, Vector2D imageSize, Vector2D start_position, Vector2D size, FACING start_facing, float movement_speed, LevelMap* map);

	~Character();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	void HandleInputs(float deltaTime);
	void MoveLeft(float deltaTime);
	void MoveRight(float deltaTime);

	void Jump(float deltsTime);
	void AddGravity(float deltaTime);

	bool IsJumping() { return m_is_jumping;}
	void CancelJump();
	void SetPosition(Vector2D new_position);
	Vector2D GetPosition();
	Circle2D GetCollisionRadius();
	Rect2D GetCollisionBox() {
		return Rect2D(m_position.x, m_position.y,
			m_size.x, m_size.y);
	}
	Vector2D GetSize() { return m_size; }
	bool GetInjured() { return m_injured; }
	bool GetAlive() { return m_alive; }
	void SetAlive(bool isAlive) { m_alive = isAlive; }

	void FlipDirection();

};
