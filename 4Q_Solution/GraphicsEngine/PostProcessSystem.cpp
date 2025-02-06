#include "pch.h"
#include "PostProcessSystem.h"

// Filters
#include "Bloom.h"
#include "Blur.h"
#include "SSAO.h"

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

	SSAO* pSSAO = new SSAO;
	pSSAO->Initialize();
	_filters[(int)GE::FilterType::SSAO] = { 1 << _ID++, pSSAO };

	Blur* pBlur = new Blur;
	pBlur->Initialize();
	_filters[(int)GE::FilterType::Blur] = { 1 << _ID++, pBlur };

	Vector2 screenSize{ g_width, g_height };
	g_pConstantBuffer->UpdateConstantBuffer(L"ScreenSize", &screenSize);
}

void PostProcessSystem::Free()
{
	for (auto& [ID, filter] : _filters)
	{
		delete filter;
	}
}