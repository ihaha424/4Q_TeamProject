#pragma once

namespace Engine::Component
{
	class Text : public GraphicsComponent
	{
	public:
		Text();

	public:
		void SetFontPath(const std::filesystem::path& fontPath);

		void Initialize(const Modules& modules) override;
		void Attach() override;
		void Detach() override;
		void Finalize() override;

		void SetFont(const wchar_t* font) const;
		void SetFontScale(const float x, const float y) const;
		void SetFontColor(const float r, const float g, const float b, const float a) const;
		void SetLayerDepth(const float depth) const;
		void SetPivot(const float x, const float y) const;
		void SetRotationFromDegree(const float degree) const;
		void SetPosition(const float x, const float y, const float z = 0.f) const;
		void SetText(const wchar_t* text) const;

	private:
		GE::ITextRenderer* _geTextRenderer;
		std::filesystem::path _fontPath;
	};
}