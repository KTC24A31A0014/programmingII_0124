#include "shape_container.h"

void ShapeContainer::draw(const CommandList& commandList, UINT64 id) noexcept
{
	auto it = shapes_.find(id);
	if (it == shapes_.end())
	{
		//指定された形状が存在しない場合は何もしない
		return;
	}

	it->second->draw(commandList);
}