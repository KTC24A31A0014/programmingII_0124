//ゲームクラス
#pragma once

#include "game_object.h"

namespace game
{
	class Player : public GameObject
	{
		public:
			Player() = default;
			virtual ~Player() = default;

			virtual void initialize() noexcept override;

			virtual void update() noexcept override;
	};
}