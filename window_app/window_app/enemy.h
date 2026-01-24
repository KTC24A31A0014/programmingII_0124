//敵制御クラス
#pragma once

#include "game_object.h"

namespace game
{
	class Enemy : public GameObject
	{
		public:
			Enemy() = default;
			virtual ~Enemy() = default;

			virtual void initialize() noexcept override;

			virtual void update() noexcept override;

			virtual void onHit() noexcept override;
	};
}