//コンスタントバッファクラス
#pragma once

#include "device.h"
#include "descriptor_heap.h"

class ConstantBuffer final
{
	public:
		ConstantBuffer() = default;
		~ConstantBuffer();

		[[nodiscard]] bool create(UINT bufferSize) noexcept;

		[[nodiscard]] ID3D12Resource* constantBuffer() const noexcept;

		[[nodiscard]] D3D12_GPU_DESCRIPTOR_HANDLE getGpuDescriptorHandle() const noexcept;

	private:
		Microsoft::WRL::ComPtr<ID3D12Resource>	constantBuffer_{};	//コンスタントバッファ
		UINT									descriptorIndex_{};	//ディスクリプタインデックス
		D3D12_GPU_DESCRIPTOR_HANDLE				gpuHandle_{};		//GPU用 ディスクリプタハンドル
};

