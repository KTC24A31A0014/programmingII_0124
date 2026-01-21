#include "fence.h"
#include <cassert>

[[nodiscard]] bool fence::create() noexcept
{
	//フェンスの作成
	HRESULT hr = device::instance().get()->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence_));
	if (FAILED(hr))
	{
		assert(false && "フェンスの作成に失敗しました");
		return false;
	}

	//GPU 同期用のイベントハンドルを作成
	waitGpuEvent_ = CreateEvent(nullptr, false, false, "WAIT_GPU");
	if (!waitGpuEvent_)
	{
		assert(false && "GPU 同期用のイベントハンドルの作成に失敗しました");
		return false;
	}
	return true;
}

void fence::wait(UINT64 fenceValue) const noexcept
{
	if (!fence_)
	{
		assert(false && "フェンスが未作成です");
		return;
	}

	//フェンスの値が指定された値に達するまで待機
	if (fence_->GetCompletedValue() < fenceValue)
	{
		fence_->SetEventOnCompletion(fenceValue, waitGpuEvent_);
		WaitForSingleObject(waitGpuEvent_, INFINITE);
	}
}