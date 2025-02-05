#pragma once

class StaticObject : public Engine::Object
{
public:
	explicit StaticObject(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath);

	void Prepare(Engine::Content::Factory::Component* componentFactory) override;

	/**
			Set Property
	 **/
	void SetMeshData(bool meshData);
	void SetBoxScale(Engine::Math::Vector3 boxScale);

protected:
	void DisposeComponents() override;

	void PreInitialize(const Engine::Modules& modules) override;
	

protected:
	Engine::Component::StaticMesh* _staticMesh;
	std::filesystem::path _meshPath;
	Engine::Math::Matrix _matrix;

	Engine::Component::RigidStatic* _rigidStatc;
	std::filesystem::path _physicsPath;

	bool _meshData;
	Engine::Math::Vector3 _boxScale;
};

