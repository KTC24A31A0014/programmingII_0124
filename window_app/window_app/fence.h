//フェンス(CPUとGPUの動機)

#pragma once

#include "device.h"

class fence final
{
	public:
		fence() = default;
		~fence() = default;

		[[nodiscard]] bool create() noexcept;

		void wait(UINT64 fenceValue) const noexcept;

		[[nodiscard]] ID3D12Fence* get() const noexcept;

	private:
		Microsoft::WRL::ComPtr<ID3D12Fence> fence_{};			//フェンス
		HANDLE								waitGpuEvent_{};	//GPU と CPU 同期用のイベントハンドル
};

