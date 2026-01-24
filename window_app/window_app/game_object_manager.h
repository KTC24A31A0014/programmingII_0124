//ゲームオブジェクト管理クラス
#pragma once

#include "game_object.h"

#include <functional>

namespace game
{
	class GameObjectManager final
	{
		public:
			static GameObjectManager& instance() noexcept
			{
				static GameObjectManager instance;
				return instance;
			}

		public:
			void update() noexcept;

			void postUpdate() noexcept;

			void draw(const CommandList& commandList) noexcept;

			void clear() noexcept;

			[[nodiscard]] std::optional<GameObject*> gameObject(UINT64 handle) noexcept;

			void registerHit(UINT64 handle) noexcept;

			template <typename T, typename... Args>
			[[nodiscard]] UINT64 createObject(Args&&... args) noexcept
			{
				static_assert(std::is_base_of<GameObject, T>::value, "GameObjectではないモノを作ろうとしています");
				const auto handle = ++counter_;
				
				auto func = [... a = std::forward<Args>(args)]() mutable
					{
						auto p = std::make_unique<T>(std::move(a)...);
						p->setTypeId(id::get<T>());
						return p;
					};
				registerCreation(std::move(func), handle);

				return handle;
			}

			void registerDelete(UINT64 hadle) noexcept;

		private:
			void registerCreation(std::function<std::unique_ptr<GameObject>()> creation, const UINT64 handle) noexcept;

			GameObjectManager() = default;
			~GameObjectManager();

			GameObjectManager(const GameObjectManager& r)				= delete;
			GameObjectManager& operator = (const GameObjectManager& r)	= delete;
			GameObjectManager(GameObjectManager&& r)					= delete;
			GameObjectManager& operator = (GameObjectManager&& r)		= delete;

			UINT64 counter_{};
	};
}