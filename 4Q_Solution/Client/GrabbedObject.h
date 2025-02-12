#pragma once
#include "TriggerBox.h"

class GrabbedObject
	: public Engine::Object
{
public:
	explicit GrabbedObject(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath);
	virtual ~GrabbedObject() = default;
	void Prepare(Engine::Content::Factory::Component* componentFactory) override;

	void PreUpdate(float deltaTime) override;
	void PostUpdate(float deltaTime) override;

	/**
		Set Property
	 **/
	void SetIsPublic(bool isPublic);
	void SetisDynamic(bool isDynamic);
	void SetHasMesh(bool hasMesh);
	void SetBoxScale(Engine::Math::Vector3 boxScale);
	void SetBoxPosition(Engine::Math::Vector3 boxPosition);


	bool Grabbed(Engine::Transform* ownerTransform);
	void PutThis();

protected:
	void DisposeComponents() override;
	void PreInitialize(const Engine::Modules& modules) override;

protected:
	Engine::Component::StaticMesh* _staticMesh;
	std::filesystem::path _meshPath;
	Engine::Math::Matrix _matrix;

	Engine::Component::RigidKinematic* _rigidKinematic;
	std::filesystem::path _physicsPath;

protected:
	bool _isPublic;
	bool _isDynamic;
	bool _hasMesh;
	Engine::Math::Vector3 _boxScale;
	Engine::Math::Vector3 _boxPosition;

	Engine::Transform* _catchOnwerTransform;
	Engine::Transform  _prevOnwerTransform;
	float	_moveSpeed;
	float	_maxRotation;
	float	_minDistance;
	float	_maxDistance;
};
