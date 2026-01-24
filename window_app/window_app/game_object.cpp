#include "game_object.h"
#include "shape_container.h"

#include <cmath>

namespace
{
	struct ConstBufferData
	{
		DirectX::XMMATRIX world_{};
		DirectX::XMFLOAT4 color_{};
	};
}

namespace game
{
	void GameObject::initialize() noexcept
	{
		createDrawBuffer();
	}

	void GameObject::setDrawCommand(const CommandList& commandList, UINT slot) noexcept
	{
		Object::setDrawCommand(commandList, slot);
		ShapeContainer::instance().draw(commandList, shapeId_);
	}

	void GameObject::createDrawBuffer() noexcept
	{
		if (!constantBuffer_.create(sizeof(ConstBufferData)))
		{
			assert(false && "GameObject コンスタントバッファの作成に失敗しました");
		}
	}

	void GameObject::updateDrawBuffer() noexcept
	{
		Object::updateConstantBuffer(ConstBufferData{ DirectX::XMMatrixTranspose(world_), color_ });
	}

	void GameObject::setHandle(UINT64 handle) noexcept
	{
		handle_ = handle;
	}

	[[nodiscard]] UINT64 GameObject::handle() const noexcept
	{
		return handle_;
	}

	void GameObject::set(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 rot, DirectX::XMFLOAT3 scale, DirectX::XMFLOAT4 color, UINT64 shapeId) noexcept
	{
		//ワールド行列の計算
		DirectX::XMMATRIX matScale		= DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);
		DirectX::XMMATRIX rotation		= DirectX::XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
		DirectX::XMMATRIX translation	= DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
		world_							= matScale * rotation * translation;

		//カラーの設定
		color_ = color;

		//形状識別子の設定
		shapeId_ = shapeId;

		//衝突判定用の半径を設定
		radius_ = (scale.x + scale.y + scale.z) / (3.0f * 2.0f);
	}

	[[nodiscard]] DirectX::XMMATRIX GameObject::world() const noexcept
	{
		return world_;
	}

	[[nodiscard]] DirectX::XMFLOAT4 GameObject::color() const noexcept
	{
		return color_;
	}
}