#pragma once

namespace Engine::Manager::GraphicsSystem
{
	struct IRenderSystem
	{
		IRenderSystem() = default;
		IRenderSystem(const IRenderSystem& other) = default;
		IRenderSystem(IRenderSystem&& other) noexcept = default;
		IRenderSystem& operator=(const IRenderSystem& other) = default;
		IRenderSystem& operator=(IRenderSystem&& other) noexcept = default;
		virtual ~IRenderSystem() = default;

		virtual void CreateMatrix(GE::IMatrix** matrix) const = 0;
		virtual void CreateMeshRenderer(GE::IMeshRenderer** component, const GE::MESH_RENDERER_DESC* desc) const = 0;
		virtual void RegisterRenderQueue(GE::IMeshRenderer* component, GE::IMatrix* matrix) const = 0;
		virtual void UnRegisterRenderQueue(GE::IMeshRenderer* component) const = 0;
	};

	class RenderSystem final : public IRenderSystem
	{
	public:
		RenderSystem() = default;

		void Initialize(GE::IRenderSystem* renderSystem, const GE::RENDERER_DESC* desc);
		void Render() const;
		void Finalize();

		void CreateMatrix(GE::IMatrix** matrix) const override;
		void CreateMeshRenderer(GE::IMeshRenderer** component, const GE::MESH_RENDERER_DESC* desc) const override;
		void RegisterRenderQueue(GE::IMeshRenderer* component, GE::IMatrix* matrix) const override;
		void UnRegisterRenderQueue(GE::IMeshRenderer* component) const override;

		void RegisterFont(const wchar_t* name, const wchar_t* filePath) const;
		void CreateTextRenderer(GE::ITextRenderer** textRenderer) const;
		void RegisterRenderQueue(GE::ITextRenderer* textRenderer) const;
		void UnRegisterRenderQueue(GE::ITextRenderer* textRenderer) const;

	private:
		GE::IRenderSystem* _renderSystem;
		GE::ITextSystem* _textSystem;
	};
}