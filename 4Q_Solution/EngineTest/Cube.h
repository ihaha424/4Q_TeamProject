#pragma once
#include "../Packet/ProtoInclude.h"

class Cube : public Engine::Object
{
public:
	Cube(std::filesystem::path&& meshPath);

	void Prepare(Engine::Content::Factory::Component* componentFactory) override;

	void SyncLocation(const ConnectMsg::SyncObject* msg);
	void SetSerialNumber(int num);
protected:
	void DisposeComponents() override;

	void PreInitialize(const Engine::Modules& modules) override;
	void PostInitialize(const Engine::Modules& modules) override;
	void PostAttach() override;
	void PostUpdate(float deltaTime) override;
	void PostFixedUpdate() override;
private:
	std::filesystem::path _meshPath;
	Engine::Component::StaticMesh* _staticMesh;
	Engine::Math::Matrix _worldMatrix;
	Engine::Component::Synchronize* _sync;
};

