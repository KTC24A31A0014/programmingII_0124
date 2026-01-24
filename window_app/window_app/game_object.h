//ゲームクラス
#pragma once

#include <DirectXMath.h>
#include "object.h"

namespace game
{
	class GameObject : public Object
	{
		public:
			GameObject() = default;
			GameObject(UINT64 parent) : parent_(parent){}

			virtual ~GameObject() = default;

			virtual void initialize() noexcept override;

			virtual void update() noexcept override {};

			virtual void setDrawCommand(const CommandList& commandList, UINT slot) noexcept override;

			virtual void createDrawBuffer() noexcept override;

			virtual void updateDrawBuffer() noexcept override;

			virtual void onHit() noexcept {};

			[[nodiscard]] virtual UINT64 hitTargetTypeId() noexcept { return {}; }

			void setHandle(UINT64 handle) noexcept;

			[[nodiscard]] UINT64 handle() const noexcept;

			void set(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 rot, DirectX::XMFLOAT3 scale, DirectX::XMFLOAT4 color, UINT64 shapeId) noexcept;

			[[nodiscard]] DirectX::XMMATRIX world() const noexcept;

			[[nodiscard]] DirectX::XMFLOAT4 color() const noexcept;

			[[nodiscard]] float radius() noexcept { return radius_; };


		protected:
			DirectX::XMMATRIX world_ = DirectX::XMMatrixIdentity();					///ワールド行列
			DirectX::XMFLOAT4 color_ = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);	/// カラー(RGBA)
			UINT64 shapeId_{};														/// 形状識別子
			UINT64 handle_{};														/// ゲームオブジェクトハンドル
			UINT64 parent_{};														/// 親オブジェクトハンドル
			float radius_{};														/// 当たり判定用半径
	};
}