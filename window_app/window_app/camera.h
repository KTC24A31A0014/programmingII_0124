#pragma once

#include "object.h"
#include <DirectXMath.h>

namespace game
{
	class Camera final : public Object
	{
	public:
		Camera() = default;
		virtual ~Camera() = default;

		virtual void initialize() noexcept override;

		virtual void update() noexcept override;

		virtual void createDrawBuffer() noexcept override;

		virtual void updateDrawBuffer() noexcept override;

		[[nodiscard]] DirectX::XMMATRIX XM_CALLCONV viewMatrix() const noexcept;

		[[nodiscard]] DirectX::XMMATRIX XM_CALLCONV projection() const noexcept;

	private:
		DirectX::XMMATRIX view_{};
		DirectX::XMMATRIX projection_{};

		//カメラのパラメータ
		DirectX::XMFLOAT3 position_{};	/// カメラの位置
		DirectX::XMFLOAT3 target_{};	/// カメラの注視点
		DirectX::XMFLOAT3 up_{};		/// カメラの上方向
	};
}