//三角形ポリゴンクラス
#pragma once

#include "shape.h"

class TrianglePolygon final : public Shape
{
	public:
		TrianglePolygon() = default;
		~TrianglePolygon() = default;

	private:
		[[nodiscard]] virtual bool createVertexBuffer() noexcept override;

		[[nodiscard]] virtual bool createIndexBuffer() noexcept override;

};

