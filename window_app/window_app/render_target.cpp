#include "render_target.h"

#include <cassert>

namespace
{
	constexpr auto heapType_ = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
}

RenderTarget::~RenderTarget()
{
	renderTarget_.clear();
}

[[nodiscard]] bool RenderTarget::createBackBuffer(const SwapChain& swapChain) noexcept
{
	//スワップチェインの設定を取得
	const auto& desc = swapChain.getDesc();

	//レンダーターゲットリソースのサイズを設定
	renderTarget_.resize(desc.BufferCount);

	//ディスクリプタヒープの取得
	auto heap = DescriptorHeapContainer::instance().get(heapType_);

	//ディスクリプタヒープのハンドルを取得
	auto handle = heap->GetCPUDescriptorHandleForHeapStart();

	//バックバッファの生成
	for (uint8_t i = 0; i < desc.BufferCount; ++i)
	{
		const auto hr = swapChain.get()->GetBuffer(i, IID_PPV_ARGS(&renderTarget_[i]));
		if (FAILED(hr))
		{
			assert(false && "バックバッファの取得に失敗しました");
			return false;
		}

		//レンダーターゲットビューを作成してディスクリプタヒープのハンドルと関連付ける
		device::instance().get()->CreateRenderTargetView(renderTarget_[i].Get(), nullptr, handle);

		//次のハンドルへ移動
		handle.ptr += device::instance().get()->GetDescriptorHandleIncrementSize(heapType_);
	}

	return true;
}

[[nodiscard]] D3D12_CPU_DESCRIPTOR_HANDLE RenderTarget::getCpuDescriptorHandle(UINT index) const noexcept
{
	if (index >= renderTarget_.size() || !renderTarget_[index])
	{
		assert(false && "不正なレンダーターゲットです");
	}

	//ディスクリプターヒープの取得
	auto heap = DescriptorHeapContainer::instance().get(heapType_);

	//ディスクリプタヒープのハンドルを取得
	auto handle = heap->GetCPUDescriptorHandleForHeapStart();

	//インデックスに応じてハンドルを移動
	handle.ptr += index * device::instance().get()->GetDescriptorHandleIncrementSize(heapType_);
	return handle;
}

[[nodiscard]] ID3D12Resource* RenderTarget::get(UINT index) const noexcept
{
	if (index >= renderTarget_.size() || !renderTarget_[index])
	{
		assert(false && "不正なレンダーターゲットです");
		return nullptr;
	}
	return renderTarget_[index].Get();
}