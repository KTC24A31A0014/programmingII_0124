#include "object.h"

namespace game
{
	void Object::setDrawCommand(const CommandList& commandList, UINT slot) noexcept
	{
		//コマンドバッファの設定
		commandList.get()->SetGraphicsRootDescriptorTable(slot, constantBuffer_.getGpuDescriptorHandle());
	}
}