#pragma once
#include "InteractObject.h"

class Obj_Bermiore_Fabric : public InteractObject
{
public:
	explicit Obj_Bermiore_Fabric(const std::filesystem::path& meshPath, const std::filesystem::path& physicsPath);
	virtual ~Obj_Bermiore_Fabric() = default;

	void Prepare(Engine::Content::Factory::Component* componentFactory) override;
	void Interact() override;
	void DataChangeCallBack(const std::wstring& name, const std::any& value) override;
	void SendInteractToServer();
	void SetActive(const PlayMsg::ObjectActive* msg);
	void InteractCallback(const PlayMsg::InteractObject* msg);
protected:
	void DisposeComponents() override;
	void PreInitialize(const Engine::Modules& modules) override;

	Engine::Component::Synchronize* _sync;
	bool _activate;
	bool _answer;
};

