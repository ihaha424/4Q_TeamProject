#include "pch.h"
#include "RenderGroup.h"
#include "MeshRenderer.h"

void RenderGroup::Initialize(unsigned int maxLayer)
{
	_datas = new std::list<RenderData>[maxLayer];
	_maxLayer = maxLayer;
}

void RenderGroup::RegisterRenderQueue(const unsigned int layer, GE::IMeshRenderer* pMeshRenderer, GE::IMatrix* pMatrix)
{
	auto compare = [pMeshRenderer](const auto& pComponent)
		{ return static_cast<MeshRenderer*>(pMeshRenderer)->GetID() == pComponent.first->GetID();};

	if (std::ranges::any_of(_datas[layer], compare))
	{
		ASSERT(false, L"이미 등록된 MeshRenderer 입니다.");
		return;
	}

	_datas[layer].emplace_back(static_cast<MeshRenderer*>(pMeshRenderer), static_cast<Matrix4x4*>(pMatrix));
}

void RenderGroup::UnRegisterRenderQueue(const unsigned int layer, GE::IMeshRenderer* pMeshRenderer)
{
	std::erase_if(_datas[layer], [pMeshRenderer](const auto& datas)
		{ return static_cast<MeshRenderer*>(pMeshRenderer)->GetID() == datas.first->GetID(); });
}

void RenderGroup::Free()
{
	delete[] _datas;
}