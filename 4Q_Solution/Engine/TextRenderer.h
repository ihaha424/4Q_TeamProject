#pragma once

namespace Engine::Component
{
	class TextRenderer : public GraphicsComponent
	{
	public:
		TextRenderer(std::filesystem::path font);

	public:
		void Initialize() override;
		void Attach() override;
		void Detach() override;
		void Finalize() override;

		void SetFont(const wchar_t* font);
		void SetFontScale(const float x, const float y);
		void SetFontColor(const float r, const float g, const float b, const float a);
		void SetLayerDepth(const float depth);
		void SetPivot(const float x, const float y);
		void SetRotationFromDegree(const float degree);
		void SetPosition(const float x, const float y, const float z = 0.f);
		void SetText(const wchar_t* text);

	private:
		GE::ITextRenderer* _geTextRenderer;
		std::filesystem::path _font;
	};
}