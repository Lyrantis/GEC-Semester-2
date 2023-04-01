#include "Collisions.h"
#include "Character.h"

Collisions* Collisions::m_instance = nullptr;

Collisions::Collisions() {

}

Collisions::~Collisions() {

	m_instance = nullptr;
}

Collisions* Collisions::Instance() {

	if (!m_instance) {
		m_instance = new Collisions;
	}

	return m_instance;
}

bool Collisions::Circle(Circle2D circle1, Circle2D circle2) {

	Vector2D vec = Vector2D(circle1.x - circle2.x, circle1.y - circle2.y);

	double dist = sqrt((vec.x * vec.x) + (vec.y * vec.y));

	double combinedDist = circle1.r + circle2.r;

	return dist < combinedDist;
}

bool Collisions::Box(Rect2D rect1, Rect2D rect2) {

	if (rect1.x + (rect1.w / 2) > rect2.x &&
		rect1.x + (rect1.w / 2) < rect2.x + rect2.w &&
		rect1.y + (rect1.h / 2) > rect2.y &&
		rect1.y + (rect1.h / 2) < rect2.y + rect2.h)
	{
		return true;
	}
	return false;

}