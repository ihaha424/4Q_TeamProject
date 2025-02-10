#include "pch.h"
#include "BaseStone.h"

BaseStone::BaseStone(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath)\
	: InteractObject(std::forward<std::filesystem::path>(meshPath), std::forward<std::filesystem::path>(physicsPath))
	, myManager{}
{
}

void BaseStone::Prepare(Engine::Content::Factory::Component* componentFactory)
{
	InteractObject::Prepare(componentFactory);
}

void BaseStone::DisposeComponents()
{
	InteractObject::DisposeComponents();
}

void BaseStone::PreInitialize(const Engine::Modules& modules)
{
	InteractObject::PreInitialize(modules);

	myManager = modules.gameStateManager->FindSubManager(L"puzzle_00");
	myManager->Subscribe(L"Data", [this](const std::wstring& name, const std::any& value)
								{
									DataChangeCallBack(name, value);
								}
	, this);
}


