#include "pch.h"
#include "PostProcessSystem.h"

// Filters
#include "Bloom.h"

void PostProcessSystem::AddFilter(const unsigned int layer, GE::IFilter* pFilter)
{
	ASSERT((layer >= g_pRenderGroup->GetMaxLayer()), L"레이어 범위를 초과했습니다.");
	_filters[layer].push_back(reinterpret_cast<Filter*>(pFilter));
}

void PostProcessSystem::CreateBloom(GE::IBloom** ppBloom)
{
	(*ppBloom) = new Bloom;
}

void PostProcessSystem::Initialize(const unsigned int layer)
{
	_filters = new std::vector<Filter*>[layer];
}

void PostProcessSystem::Free()
{
	delete[] _filters;
}
