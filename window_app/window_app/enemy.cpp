#include "enemy.h"
#include "shape_container.h"
#include "triangle_polygon.h"

namespace game
{
	void Enemy::initialize() noexcept
	{
		GameObject::initialize();

		auto triId = ShapeContainer::instance().create<TrianglePolygon>();
		set({ 0.0f, 0.0f, 30.0f }, { 0.0f, 0.0f, 0.0f }, { 10.0f, 10.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1 }, triId);
	}

	void Enemy::update()
	{

	}

	void Enemy::onHit()
	{
		color_.y = 0.95f;
		color_.z = 0.95f;
	}
}