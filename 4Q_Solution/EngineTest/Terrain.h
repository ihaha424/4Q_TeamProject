#pragma once

class BG_Terrain : public Engine::Object
{
public:
	explicit BG_Terrain(std::filesystem::path&& meshPath);

	void Prepare(Engine::Content::Factory::Component* componentFactory) override;

protected:
	void DisposeComponents() override;

	void PreInitialize(const Engine::Modules& modules) override;
	void PostInitialize(const Engine::Modules& modules) override;

private:
	Engine::Component::StaticMesh* _staticMesh;
	std::filesystem::path _meshPath;
	Engine::Math::Matrix _matrix;

	Engine::Component::RigidStatic* _terrainMesh;

};

