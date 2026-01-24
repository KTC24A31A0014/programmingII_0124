#include "camera.h"

#include <cmath>

namespace
{
	//定数
	constexpr float eyeMoveSpeed_ = 0.06f;		// カメラ移動速度
	constexpr float destTargetToView_ = -5.0f;	// 注視点からカメラまでの距離


	struct ConstBufferData
	{
		DirectX::XMMATRIX view_{};			/// ビュー行列
		DirectX::XMMATRIX projection_{};	/// 射影行列
	};
}

namespace game
{
	void Camera::initialize() noexcept
	{
		createDrawBuffer();

		//カメラの位置を設定
		position_ = DirectX::XMFLOAT3(0.0f, 1.5f, destTargetToView_);

		//カメラの注視点を設定
		target_ = DirectX::XMFLOAT3(0.0f, 0.0f, 10.0f);

		//カメラの上方向を設定
		up_ = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);

		//プロジェクション行列の設定
		projection_ = DirectX::XMMatrixPerspectiveFovLH(DirectX::XM_PIDIV4, 1280.0f / 720.0f, 0.1f, 100.0f);
	}

	void Camera::update() noexcept
	{
		//ビュー行列の計算
		view_ = DirectX::XMMatrixLookAtLH(DirectX::XMLoadFloat3(&position_), DirectX::XMLoadFloat3(&target_), DirectX::XMLoadFloat3(&up_));
	}

	void Camera::createDrawBuffer() noexcept
	{
		if (!constantBuffer_.create(sizeof(ConstBufferData)))
		{
			assert(false && "カメラ用コンスタントバッファの作成に失敗しました");
		}
	}

	void Camera::updateDrawBuffer() noexcept
	{
		Object::updateConstantBuffer(ConstBufferData{ DirectX::XMMatrixTranspose(view_), DirectX::XMMatrixTranspose(projection_)});
	}

	[[nodiscard]] DirectX::XMMATRIX XM_CALLCONV Camera::viewMatrix() const noexcept
	{
		return view_;
	}

	[[nodiscard]] DirectX::XMMATRIX XM_CALLCONV Camera::projection() const noexcept
	{
		return projection_;
	}
}