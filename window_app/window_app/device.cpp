#include "device.h"

#include <cassert>

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxguid.lib")

device::~device()
{
	//デバイスの解放
	if (device_)
	{
		device_->Release();
		device_ = nullptr;
	}
}

[[nodiscard]] bool device::create() noexcept
{
	//DXGIの作成
	if (!dxgiInstance_.setDisplayAdapter())
	{
		assert(false && "DXGIのアダプタ認定に失敗しました");
		return false;
	}

	//デバイス作成
	const auto hr = D3D12CreateDevice(dxgiInstance_.displayAdapter(), D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&device_));
	if (FAILED(hr))
	{
		assert(false && "デバイスの作成に失敗");
		return false;
	}

	return true;
}

[[nodiscard]] ID3D12Device* device::get() const noexcept
{
	if (!device_)
	{
		assert(false && "デバイスが未作成です");
	}

	return device_.Get();
}

[[nodiscard]] const DXGI& device::dxgi() const noexcept
{
	return dxgiInstance_;
}