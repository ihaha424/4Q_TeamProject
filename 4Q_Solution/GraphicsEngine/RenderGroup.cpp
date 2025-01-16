#include "pch.h"
#include "RenderGroup.h"
#include "MeshRenderer.h"

void RenderGroup::RegisterRenderQueue(GE::IMeshRenderer* pComponent, GE::IMatrix* pMatrix)
{
	_datas.emplace_back(static_cast<MeshRenderer*>(pComponent), static_cast<Matrix4x4*>(pMatrix));
}

void RenderGroup::UnRegisterRenderQueue(GE::IMeshRenderer* pComponent)
{
	std::erase_if(_datas, [pComponent](const auto& datas)
		{ return static_cast<MeshRenderer*>(pComponent)->GetID() == datas.first->GetID(); });
}

void RenderGroup::Free()
{
}