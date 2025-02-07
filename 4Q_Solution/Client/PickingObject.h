#pragma once
#include "TriggerBox.h"

class PickingObject
	: public Engine::Object
{
public:
	explicit PickingObject(std::filesystem::path&& meshPath);
	virtual ~PickingObject() = default;
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
	TriggerBox* _trigger;

protected:
	bool _isPublic;
	bool _isDynamic;
	bool _hasMesh;
	Engine::Math::Vector3 _boxScale;
};

