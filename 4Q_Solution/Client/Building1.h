#pragma once
class Building1 : public Engine::Object
{
public:
	explicit Building1(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath);

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
	std::filesystem::path _physicsPath;
};

