#include "pch.h"
#include "UnlitSystem.h"
#include "UnlitRenderer.h"
#include "LineRenderer.h"

void UnlitSystem::CreateUnlitRenderer(GE::IUnlitRenderer** ppComponent, const GE::UNLIT_RENDERER_DESC* desc)
{
	UnlitRenderer* pComponent = nullptr;

	switch (desc->type)
	{
	case GE::UNLIT_RENDERER_DESC::Type::Line:
	{
		LineRenderer* pLineRenderer = new LineRenderer;
		pLineRenderer->Initialize();
		pComponent = pLineRenderer;
		break;
	}
	default:
		break;
	}

	(*ppComponent) = pComponent;
}

void UnlitSystem::RegisterRenderQueue(GE::IUnlitRenderer* pComponent, GE::Matrix4x4* pMatrix)
{
	auto compare = [pComponent](const auto component)
		{ return static_cast<UnlitRenderer*>(pComponent)->GetID() == static_cast<UnlitRenderer*>(component.first)->GetID(); };

	if (std::ranges::any_of(_components, compare))
	{
		ASSERT(false, L"Already registered UnlitRenderer.");
		return;
	}

	_components.emplace_back(dynamic_cast<UnlitRenderer*>(pComponent), static_cast<Matrix*>(pMatrix));
}

void UnlitSystem::UnRegisterRenderQueue(GE::IUnlitRenderer* pComponent)
{
	std::erase_if(_components, [pComponent](const auto& component)
		{ return dynamic_cast<UnlitRenderer*>(pComponent)->GetID() == static_cast<UnlitRenderer*>(component.first)->GetID(); });
}

void UnlitSystem::Initialize()
{
	_pDeviceContext = g_pGraphicDevice->GetDeviceContext();

	D3D11_RASTERIZER_DESC desc
	{
		.FillMode = D3D11_FILL_SOLID,
		.CullMode = D3D11_CULL_NONE,
		.FrontCounterClockwise = FALSE,
		.DepthClipEnable = TRUE
	};

	ID3D11Device* pDevice = g_pGraphicDevice->GetDevice();
	pDevice->CreateRasterizerState(&desc, &_pRSState);
}

void UnlitSystem::Render()
{
	auto* pBackBuffer = g_pGraphicDevice->GetBackBuffer();
	auto* pDepth = g_pViewManagement->GetDepthStencilView(L"DefaultDepth");

	_pDeviceContext->OMSetRenderTargets(1, &pBackBuffer, pDepth);
	_pDeviceContext->RSSetState(_pRSState);

	for (auto& [component, matrix] : _components)
		dynamic_cast<UnlitRenderer*>(component)->Render();

	_pDeviceContext->RSSetState(nullptr);
}

void UnlitSystem::Free()
{
	SafeRelease(_pRSState);
}