#pragma once

namespace Engine::UI::Wrapper
{
	class Image : public Wrapper
	{
	public:
		Image(Math::Rect* rect, const std::filesystem::path& path);

		void Initialize(const Modules& modules) override;
		void Attach() override;
		void Update(float deltaGameTime) override;
		void FixedUpdate() override;
		void Detach() override;
		void Finalize() override;

	protected:
		Component::Sprite _sprite;

	private:
		std::filesystem::path _path;
		Math::Matrix _matrix;
	};
}