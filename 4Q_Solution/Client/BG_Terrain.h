#pragma once

class BG_Terrain : public Engine::Object
{
public:
	BG_Terrain(const std::filesystem::path& meshPath, const std::filesystem::path& physicsPath);
	/**
		Set Property
 **/
	void SetIsPublic(bool isPublic);
	void SetisDynamic(bool isDynamic);
	void SetHasMesh(bool hasMesh);
	void SetBoxScale(Engine::Math::Vector3 boxScale);
	void SetBoxPosition(Engine::Math::Vector3 boxPosition);
	void SetIsSphere(bool isSphere);

public:
	void PreInitialize(const Engine::Modules& modules) override;
	void Prepare(Engine::Content::Factory::Component* componentFactory) override;
	void DisposeComponents() override;
	void PreUpdate(float deltaTime) override;

protected:
	Engine::Component::StaticMesh* _staticMesh;
	std::filesystem::path _meshPath;
	Engine::Math::Matrix _matrix;
	std::filesystem::path _physicsPath;
protected:
	bool _isPublic;
	bool _isDynamic;
	bool _hasMesh;
	bool _isSphere;

};
