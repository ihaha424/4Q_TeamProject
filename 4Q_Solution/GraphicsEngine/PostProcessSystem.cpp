#include "pch.h"
#include "PostProcessSystem.h"

// Filters
#include "Bloom.h"
#include "Blur.h"

void PostProcessSystem::GetFilter(GE::IFilter** ppFilter, GE::FilterType type)
{
	(*ppFilter) = reinterpret_cast<GE::IFilter*>(_filters[(int)type].second);
}

void PostProcessSystem::Initialize()
{
	_filters.resize((size_t)GE::FilterType::End);

	Bloom* pBloom = new Bloom;
	pBloom->Initialize();
	_filters[(int)GE::FilterType::Bloom] = { 1 << _ID++, pBloom };

	//pBloom = new Bloom;
	////pBloom->Initialize();
	//_filters[(int)GE::FilterType::Blur] = { 1 << _ID++, pBloom };

	Blur* pBlur = new Blur;
	pBlur->Initialize();
	_filters[(int)GE::FilterType::Blur] = { 1 << _ID++, pBlur };
}

void PostProcessSystem::Free()
{
	for (auto& [ID, filter] : _filters)
	{
		delete filter;
	}
}