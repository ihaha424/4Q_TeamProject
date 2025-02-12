#pragma once

namespace Engine::Component
{
	class Sprite : public GraphicsComponent
	{
	public:
		Sprite();

	public:
		void Initialize(const Modules& modules) override;
		void Attach() override;
		void Update(float deltaTime) override;
		void Detach() override;
		void Finalize() override;

	public:
		void SetMatrix(Math::Matrix* matrix);
		void SetFilePath(const std::filesystem::path& filePath);
		void SetActiveDraw(bool isActive);

	private:
		GE::Matrix4x4			_geWorld;
		std::filesystem::path	_filePath;
		GE::ISpriteRenderer*	_geSpriteRenderer;
		GE::SpriteDescription	_geSpriteDescription;
		GE::Matrix4x4*			_geMatrix;
		float					_width;
		float					_height;
	};
}