#pragma once

namespace Engine::Component
{
	class Sprite : public GraphicsComponent
	{
	public:
		Sprite();

	public:
		void Attach() override;
		void Detach() override;
		void Finalize() override;

	public:
		void SetMatrix(Math::Matrix* matrix);
		void SetFilePath(const std::filesystem::path& filePath);
		void SetActiveDraw(bool isActive);

	private:
		std::filesystem::path _filePath;
		GE::ISpriteRenderer* _geSpriteRenderer;
		GE::SpriteDescription _geSpriteDescription;
		GE::Matrix4x4* _geMatrix;
	};
}