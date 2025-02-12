#pragma once

namespace Engine::UI::Element
{
	class Text : public UserInterface
	{
	public:
		explicit Text(Math::Rect* rect);
		Text(Math::Rect* rect, const std::wstring& text);

		void SetText(const std::wstring& text);

	private:
		std::wstring _text;
	};
}
