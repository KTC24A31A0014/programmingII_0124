// 形状ベースクラス

#pragma once

#include "device.h"
#include "command_list.h"

#include <DirectXMath.h>

class Shape
{
	public:
		struct ConstBufferData
		{
			DirectX::XMMATRIX world_{};	///ワールド行列
			DirectX::XMFLOAT4 color_{};	///カラー（RGBA）
		};

		Shape() = default;
		
		virtual ~Shape() = default;

		[[nodiscard]] bool create() noexcept;

		void draw(const CommandList& commandList) noexcept;

	protected:
		[[nodiscard]] virtual bool createVertexBuffer() noexcept = 0;

		[[nodiscard]] virtual bool createIndexBuffer() noexcept = 0;

		Microsoft::WRL::ComPtr<ID3D12Resource>	vertexBuffer_{};		///頂点バッファ
		Microsoft::WRL::ComPtr<ID3D12Resource>	indexBuffer_{};			///インデックスバッファ
		D3D12_VERTEX_BUFFER_VIEW				vertexBufferView_{};	///頂点バッファビュー
		D3D12_INDEX_BUFFER_VIEW					indexBufferView_{};		///インデックスバッファビュー
		D3D_PRIMITIVE_TOPOLOGY					topology_{};			///プリミティブトポロジー
		UINT									indexCount_{};			///インデックス数
};

