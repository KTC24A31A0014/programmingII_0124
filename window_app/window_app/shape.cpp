#include "shape.h"

#include <cassert>

[[nodiscard]] bool Shape::create() noexcept
{
	//頂点バッファの生成
	if (!createVertexBuffer())
	{
		return false;
	}

	//インデックスバッファの生成
	if (!createIndexBuffer())
	{
		return false;
	}

	return true;
}

void Shape::draw(const CommandList& commandList) noexcept
{
	//頂点バッファのせってい
	commandList.get()->IASetVertexBuffers(0, 1, &vertexBufferView_);

	//インデックスバッファの設定
	commandList.get()->IASetIndexBuffer(&indexBufferView_);

	//プリミティブ形状の設定
	commandList.get()->IASetPrimitiveTopology(topology_);

	//描画コマンド
	commandList.get()->DrawIndexedInstanced(indexCount_, 1, 0, 0, 0);
}