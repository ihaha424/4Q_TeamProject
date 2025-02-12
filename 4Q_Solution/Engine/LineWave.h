#pragma once

namespace Engine::Component
{
	class LineWave : public GraphicsComponent
	{
	public:
		LineWave();

	public:
		void Initialize(const Modules& modules) override;
		void Attach() override;
		void LateUpdate(float deltaTime) override;
		void Detach() override;
		void Finalize() override;

	public:
		void SetBaseTexturePath(const std::filesystem::path& filePath);
		void SetMaskTexturePath(const std::filesystem::path& filePath);
		void SetGradientTexturePath(const std::filesystem::path& filePath);
		void SetSourcePosition(const Engine::Math::Vector3* source);
		void SetDestinationPosition(const Engine::Math::Vector3* destination);
		void SetSegment(unsigned int segments);
		void SetPostEffectLayer(unsigned int layer);

	private:
		GE::Matrix4x4 _geMatrix;
		std::filesystem::path _baseTexturePath;
		std::filesystem::path _masktexturePath;
		std::filesystem::path _gradientTexturePath;
		GE::ILineRenderer* _geLineRenderer;
	};
}