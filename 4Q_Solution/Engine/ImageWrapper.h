#pragma once

namespace Engine::UI::Wrapper
{
	class Image : public Wrapper
	{
	public:
		Image(Math::Rect* rect, const std::filesystem::path& path);

	private:
		std::filesystem::path _path;
	};
}