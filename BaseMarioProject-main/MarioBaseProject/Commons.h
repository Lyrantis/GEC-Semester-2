#pragma once

struct Vector2D {
	float x, y;

	Vector2D() {

		x = 0.0f;
		y = 0.0f;
	}

	Vector2D(float xIn, float yIn) {

		x = xIn;
		y = yIn;
	}
};

struct Rect2D {
	float x, y, w, h;

	Rect2D(float x_pos, float y_pos, float width, float height) {

		x = x_pos;
		y = y_pos;
		w = width;
		h = height;
	}
};

struct Circle2D {
	float x, y, r;

	Circle2D(float x, float y, float r) {
		this->x = x;
		this->y = y;
		this->r = r;
	}
};

enum SCREENS {

	SCREEN_INTRO,
	SCREEN_MENU,
	SCREEN_LEVEL1,
	SCREEN_LEVEL2,
	SCREEN_GAMEOVER,
	SCREEN_HIGHSCORES
};

enum FACING {
	FACING_LEFT,
	FACING_RIGHT
};
