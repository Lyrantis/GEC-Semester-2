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
