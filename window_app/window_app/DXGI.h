//DXGI 制御クラス 
#pragma once

#include <d3d12.h>
#include <dxgi1_4.h>

using namespace std;

class DXGI final
{
	public:
		DXGI() = default;
		~DXGI();

		[[nodiscard]] bool setDisplayAdapter() noexcept;

		[[nodiscard]] IDXGIFactory4* factory() const noexcept;

		[[nodiscard]] IDXGIAdapter1* displayAdapter() const noexcept;

	private:
		IDXGIFactory4* dxgiFactory_{};	//DXGIを作成するふぁくとりー
		IDXGIAdapter1* dxgiAdapter_{};	//ディスプレイモード取得用アダプタ
};

