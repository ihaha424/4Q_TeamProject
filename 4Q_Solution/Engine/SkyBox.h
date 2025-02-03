#pragma once

namespace Engine::Component
{
	class SkyBox final : public Mesh
	{
	public:
		SkyBox();
		
	public:
		void Initialize(const Modules& modules) override;

	public:
		void SetSkyBoxTexture(const wchar_t* filePath);
		void SetBRDFTexture(const wchar_t* filePath);
		void SetDiffuseTexture(const wchar_t* filePath);
		void SetSpecularTexture(const wchar_t* filePath);

	private:
		GE::ISkyBoxRenderer* _geSkyBox;
	};
}