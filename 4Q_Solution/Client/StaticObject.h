#pragma once

class StaticObject : public Engine::Object
{
public:
	StaticObject(const std::filesystem::path& meshPath, const std::filesystem::path& physicsPath);
	virtual ~StaticObject() = default;
	void Prepare(Engine::Content::Factory::Component* componentFactory) override;

	/**
			Set Property
	 **/
	void SetIsPublic(bool isPublic);
	void SetisDynamic(bool isDynamic);
	void SetHasMesh(bool hasMesh);
	void SetBoxScale(Engine::Math::Vector3 boxScale);
	void SetBoxPosition(Engine::Math::Vector3 boxPosition);
	void SetIsSphere(bool isSphere);

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
	bool _isSphere;
	Engine::Math::Vector3 _boxScale;
	Engine::Math::Vector3 _boxPosition;
};

