#pragma once
#include "includes/IRenderSystem.h"

class IRenderer;
class TextSystem;
class RenderSystem : public GE::IRenderSystem
{
public:
	explicit RenderSystem() = default;
	virtual ~RenderSystem() = default;

public:
	// IRenderSystem을(를) 통해 상속됨
	void Initialize(const GE::RENDERER_DESC* pDesc) override;
	void Release() override;
	void Render() override;

	void GetTextSystem(GE::ITextSystem** ppTextSystem) override;
	void GetPostProcessSystem(GE::IPostProcessSystem** ppPostProcessSystem) override;
	void CreateMatrix(GE::IMatrix** ppMatrix) override;
	void CreateMeshRenderer(GE::IMeshRenderer** ppComponent, const GE::MESH_RENDERER_DESC* pDesc) override;
	void RegisterRenderQueue(const unsigned int layer, GE::IMeshRenderer* pComponent, GE::IMatrix* pMatrix) override;
	void UnRegisterRenderQueue(const unsigned int layer, GE::IMeshRenderer* pComponent) override;

private:
	void InitializeDX11(HWND hWnd, bool isFullScreen, const unsigned int maxLayer);
	void InitializeDX12();
	void InitializeDXR();

private:
	IRenderer*					_pRenderer{ nullptr };
	TextSystem*					_pTextSystem{ nullptr };
	IDXGISwapChain*				_pSwapChain{ nullptr };
};