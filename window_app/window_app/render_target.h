//レンダーターゲット制御
#pragma once

#include "device.h"
#include "swap_chain.h"
#include "descriptor_heap.h"

#include <vector>

class RenderTarget final
{
	public:
		RenderTarget() = default;
		~RenderTarget();

		[[nodiscard]] bool createBackBuffer(const SwapChain& swapchain) noexcept;

		[[nodiscard]] D3D12_CPU_DESCRIPTOR_HANDLE getCpuDescriptorHandle(UINT index) const noexcept;

		[[nodiscard]] ID3D12Resource* get(UINT index) const noexcept;

	private:
		std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> renderTarget_{};	///レンダーターゲットリソースの配列
};

