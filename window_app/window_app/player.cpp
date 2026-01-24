#include "player.h"
#include "input.h"
#include "shape_container.h"
#include "quad_polygon.h"

#include "game_object_manager.h"
#include "bullet.h"

namespace game
{
	void Player::initialize() noexcept
	{
		GameObject::initialize();

		auto quadId = ShapeContainer::instance().create<QuadPolygon>();
		set({ -.2f, 0.0f, 0.1f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, { .0f, 1, .0f, 1 }, quadId);
	}

	void Player::update() noexcept
	{
		GameObject::update();

		constexpr float moveSpeed = 0.05f;

		//入力処理
		DirectX::XMFLOAT3 pos{};
		if (input::instance().getKey('W')) 
		{
			pos.z += moveSpeed;
		}
		if (input::instance().getKey('S'))
		{
			pos.z -= moveSpeed;
		}
		if (input::instance().getKey('A'))
		{
			pos.x -= moveSpeed;
		}
		if (input::instance().getKey('D'))
		{
			pos.x += moveSpeed;
		}

		//平行移動
		DirectX::XMVECTOR temp = DirectX::XMVectorSet(pos.x, pos.y, pos.z, 0.0f);
		world_.r[3] = DirectX::XMVectorAdd(world_.r[3], temp);

		if (input::instance().getTrigger('B'))
		{
			//球の生成
			GameObjectManager::instance().createObject<Bullet>(handle());
		}
	}
}