//形状コンテナクラス
#pragma once

#include "shape.h"
#include <unordered_map>
#include <memory>

class ShapeContainer final
{
	public:
		static ShapeContainer& instance() noexcept
		{
			static ShapeContainer instance;
			return instance;
		}

		template <class T>
		[[nodiscard]] UINT64 create() noexcept
		{
			const auto id = id::get<T>();
			if (shapes_.find(id) != shapes_.end())
			{
				//既に存在している場合は何もしない
				return id;
			}

			//形状の生成と登録
			auto p = std::make_unique<T>();
			if (!p->create())
			{
				assert(false && "形状の生成に失敗しました");
				return 0;
			}

			shapes_.emplace(id, std::move(p));
			return id;
		}

		void draw(const CommandList& commandList, UINT64 id) noexcept;

	private:
		ShapeContainer() = default;
		~ShapeContainer() = default;

		ShapeContainer(const ShapeContainer&)				= delete;
		ShapeContainer& operator = (const ShapeContainer&)	= delete;
		ShapeContainer(ShapeContainer&&)					= delete;
		ShapeContainer& operator = (ShapeContainer&&)		= delete;

	protected:
		std::unordered_map<UINT64, std::unique_ptr<Shape>> shapes_;
};

