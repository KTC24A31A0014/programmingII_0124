//球制御クラス
#pragma once

#include "game_object.h"

namespace game
{
	class Bullet : public GameObject
	{
		public:
			Bullet() = default;

			using GameObject::GameObject;

			virtual ~Bullet() = default;

			virtual void initialize() noexcept override;

			virtual void update() noexcept override;

			virtual void onHit() noexcept override;

			[[nodiscard]] virtual UINT64 hitTargetTypeId() noexcept override;
	};
}