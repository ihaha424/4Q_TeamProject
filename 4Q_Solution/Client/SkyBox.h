#pragma once

class SkyBox : public Engine::Object
{
public:
	SkyBox(std::filesystem::path&& meshPath);

	void Prepare(Engine::Content::Factory::Component* componentFactory) override;

protected:
	void DisposeComponents() override;

	void PreInitialize(const Engine::Modules& modules) override;
	void PostInitialize(const Engine::Modules& modules) override;

private:
	std::filesystem::path _meshPath;

	Engine::Component::SkyBox* _skyBox;
	Engine::Math::Matrix _worldMatrix;
};