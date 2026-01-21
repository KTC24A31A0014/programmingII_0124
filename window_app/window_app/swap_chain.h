//スワップチェイン制御クラス
#pragma once

#include "command_queue.h"

class SwapChain final
{
	public:
		SwapChain() = default;
		~SwapChain() = default;

		[[nodiscard]] bool create(const CommandQueue& commandQueue) noexcept;

		[[nodiscard]] IDXGISwapChain3* get() const noexcept;

		[[nodiscard]] const DXGI_SWAP_CHAIN_DESC1& getDesc() const noexcept;

	private:
		Microsoft::WRL::ComPtr<IDXGISwapChain3> swapChain_{};		//スワップチェイン
		DXGI_SWAP_CHAIN_DESC1					 swapChainDesc_{};	//スワップチェインの設定
};

