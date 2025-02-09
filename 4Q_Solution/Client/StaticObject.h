#pragma once

class StaticObject : public Engine::Object
{
public:
	explicit StaticObject(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath);
	virtual ~StaticObject() = default;
	void Prepare(Engine::Content::Factory::Component* componentFactory) override;

	/**
			Set Property
	 **/
	void SetIsPublic(bool isPublic);
	void SetisDynamic(bool isDynamic);
	void SetHasMesh(bool hasMesh);
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

protected:
	bool _isPublic;
	bool _isDynamic;
	bool _hasMesh;
	Engine::Math::Vector3 _boxScale;
};

