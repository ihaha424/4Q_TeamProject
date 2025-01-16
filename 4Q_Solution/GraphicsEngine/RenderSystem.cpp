#include "pch.h"
#include "RenderSystem.h"

#include "DX11Renderer.h"
#include "VIBuffer.h"

#include "StaticMeshRenderer.h"
#include "SkeletalMeshRenderer.h"
#include "TextSystem.h"

StructuredBuffer*	g_pStructuredBuffer;
ConstantBuffer*		g_pConstantBuffer;
GraphicDevice*		g_pGraphicDevice;
Sampler*			g_pSampler;
ViewManagement*		g_pViewManagement;
RenderGroup*		g_pRenderGroup;
VIBuffer*			g_pQuad;
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
		InitializeDX11(pDesc->hWnd, pDesc->isFullScreen);
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

void RenderSystem::CreateMatrix(GE::IMatrix** ppMatrix)
{
	(*ppMatrix) = new Matrix4x4;
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
	}

	pMeshRenderer->Initialize(pDesc->filePath);
	(*ppComponent) = pMeshRenderer;
}

void RenderSystem::RegisterRenderQueue(GE::IMeshRenderer* pComponent, GE::IMatrix* pMatrix)
{
	g_pRenderGroup->RegisterRenderQueue(pComponent, pMatrix);
}

void RenderSystem::UnRegisterRenderQueue(GE::IMeshRenderer* pComponent)
{
	g_pRenderGroup->UnRegisterRenderQueue(pComponent);
}

void RenderSystem::InitializeDX11(HWND hWnd, bool isFullScreen)
{
	g_pGraphicDevice = new GraphicDevice;
	g_pGraphicDevice->Initialize(hWnd, isFullScreen);
	
	g_pViewManagement = new ViewManagement;
	g_pStructuredBuffer = new StructuredBuffer;
	g_pConstantBuffer = new ConstantBuffer;
	g_pRenderGroup = new RenderGroup;

	g_pSampler = new Sampler;
	g_pSampler->Initialize();
	
	g_pQuad = new VIBuffer;

	std::vector<std::pair<Vector4, Vector2>> vertices(4);
	unsigned int indices[6];

	vertices[0] = { { -1.0f, -1.0f, 0.0f, 1.f }, { 0.0f, 1.0f } };
	vertices[1] = { { -1.0f,  1.0f, 0.0f, 1.f }, { 0.0f, 0.0f } };
	vertices[2] = { {  1.0f,  1.0f, 0.0f, 1.f }, { 1.0f, 0.0f } };
	vertices[3] = { {  1.0f, -1.0f, 0.0f, 1.f }, { 1.0f, 1.0f } };

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;

	indices[3] = 0;
	indices[4] = 2;
	indices[5] = 3;

	VIBuffer::VIBufferInfo info
	{
		.vertices = vertices.data(),
		.indices = indices,
		.vertexByteWidth = (unsigned int)vertices.size() * sizeof(std::pair<Vector4, Vector2>),
		.vertexBufferStride = sizeof(std::pair<Vector4, Vector2>),
		.vertexBufferOffset = 0,
		.indexByteWidth = sizeof(indices),
		.indexCount = 6
	};

	g_pQuad->Initialize(info);

	_pRenderer = new DX11Renderer;
	_pRenderer->Initialize();

	_pTextSystem = new TextSystem;
	_pTextSystem->Initialize();
}

void RenderSystem::InitializeDX12()
{
}

void RenderSystem::InitializeDXR()
{
}