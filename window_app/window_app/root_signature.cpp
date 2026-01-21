#include "root_signature.h"
#include <cassert>

[[nodiscard]] bool root_signature::create() noexcept
{
	//描画に必要なリソースをシェーダに伝える

	//コンスタントバッファ (スロット b0)
	//今回の場合はカメラのビュー行列や射影行列が入る想定
	D3D12_DESCRIPTOR_RANGE r0{};
	r0.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
	r0.NumDescriptors = 1;
	r0.BaseShaderRegister = 0;
	r0.RegisterSpace = 0;
	r0.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	//コンスタントバッファ（ スロット b1 ）
	//今回の場合はポリゴンのワールド行列や色が入る想定
	D3D12_DESCRIPTOR_RANGE r1{};
	r1.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
	r1.NumDescriptors = 1;
	r1.BaseShaderRegister = 1;
	r1.RegisterSpace = 0;
	r1.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	//ルートパラメータの設定
	constexpr auto paramNum = 2;
	D3D12_ROOT_PARAMETER rootParameters[paramNum]{};
	
}