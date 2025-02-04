#include "pch.h"
#include "RenderSystem.h"

#include "DX11Renderer.h"

#include "StaticMeshRenderer.h"
#include "SkeletalMeshRenderer.h"
#include "SkyBoxRenderer.h"

#include "Sampler.h"
#include "TextSystem.h"
#include "StructuredBuffer.h"

StructuredBuffer*	g_pStructuredBuffer;
ConstantBuffer*		g_pConstantBuffer;
GraphicDevice*		g_pGraphicDevice;
Sampler*			g_pSampler;
ViewManagement*		g_pViewManagement;
RenderGroup*		g_pRenderGroup;
PostProcessSystem*	g_pPostProcessSystem;
Quad*				g_pQuad;
float				g_width;
float				g_height;

void RenderSystem::Initialize(const GE::RENDERER_DESC* pDesc)
{
	g_pResourceMgr = new ResourceManager;
	g_shaderRootPath = pDesc->shaderRootPath;
	g_width = pDesc->width;
	g_height = pDesc->height;

	switch (pDesc->type)
	{
	case GE::RENDERER_DESC::Type::DX11:
		InitializeDX11(pDesc->hWnd, pDesc->isFullScreen, pDesc->maxLayer);
		break;
	case GE::RENDERER_DESC::Type::DX12:
		InitializeDX12();
		break;
	case GE::RENDERER_DESC::Type::DXR:
		InitializeDXR();
		break;
	}

	_pSwapChain = g_pGraphicDevice->GetSwapChain();
}

void RenderSystem::Release()
{
	SafeRelease(g_pPostProcessSystem);
	SafeRelease(g_pResourceMgr);
	SafeRelease(_pRenderer);
	SafeRelease(_pTextSystem);
	SafeRelease(g_pStructuredBuffer);
	SafeRelease(g_pConstantBuffer);
	SafeRelease(g_pSampler);
	SafeRelease(g_pViewManagement);
	SafeRelease(g_pRenderGroup);
	SafeRelease(g_pQuad);

	SafeRelease(g_pGraphicDevice);

	delete this;
}

void RenderSystem::Render()
{
	_pRenderer->Render();
	_pTextSystem->Render();
	_pSwapChain->Present(0, 0);
}

void RenderSystem::GetTextSystem(GE::ITextSystem** ppTextSystem)
{	
	(*ppTextSystem) = _pTextSystem;
}

void RenderSystem::GetPostProcessSystem(GE::IPostProcessSystem** ppPostProcessSystem)
{
	(*ppPostProcessSystem) = g_pPostProcessSystem;
}

void RenderSystem::CreateMeshRenderer(GE::IMeshRenderer** ppComponent, const GE::MESH_RENDERER_DESC* pDesc)
{
	MeshRenderer* pMeshRenderer = nullptr;

	switch (pDesc->type)
	{
	case GE::MESH_RENDERER_DESC::Type::Static:
		pMeshRenderer = new StaticMeshRenderer;
		break;
	case GE::MESH_RENDERER_DESC::Type::Skeletal:
		pMeshRenderer = new SkeletalMeshRenderer;
		break;
	case GE::MESH_RENDERER_DESC::Type::SkyBox:
		pMeshRenderer = new SkyBoxRenderer;
		break;
	}

	pMeshRenderer->Initialize(pDesc->filePath);
	(*ppComponent) = pMeshRenderer;
}

void RenderSystem::RegisterRenderQueue(GE::IMeshRenderer* pComponent, GE::Matrix4x4* pMatrix)
{
	g_pRenderGroup->RegisterRenderQueue(pComponent, pMatrix);
}

void RenderSystem::UnRegisterRenderQueue(GE::IMeshRenderer* pComponent)
{
	g_pRenderGroup->UnRegisterRenderQueue(pComponent);
}

void RenderSystem::InitializeDX11(HWND hWnd, bool isFullScreen, const unsigned int maxLayer)
{
	g_pGraphicDevice = new GraphicDevice;
	g_pGraphicDevice->Initialize(hWnd, isFullScreen);
	
	g_pViewManagement = new ViewManagement;
	g_pStructuredBuffer = new StructuredBuffer;
	g_pConstantBuffer = new ConstantBuffer;
	
	g_pRenderGroup = new RenderGroup;

	g_pSampler = new Sampler;
	g_pSampler->Initialize();
	
	g_pQuad = new Quad;
	g_pQuad->Initialize();

	_pRenderer = new DX11Renderer;
	_pRenderer->Initialize();

	_pTextSystem = new TextSystem;
	_pTextSystem->Initialize();

	g_pPostProcessSystem = new PostProcessSystem;
	g_pPostProcessSystem->Initialize();
}

void RenderSystem::InitializeDX12()
{
}

void RenderSystem::InitializeDXR()
{
}