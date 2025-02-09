#include "pch.h"
#include "BaseStone.h"

BaseStone::BaseStone(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath)\
	: InteractObejct(std::forward<std::filesystem::path>(meshPath), std::forward<std::filesystem::path>(physicsPath))
	, myManager{}
{
}

void BaseStone::Prepare(Engine::Content::Factory::Component* componentFactory)
{
	InteractObejct::Prepare(componentFactory);
}

void BaseStone::DisposeComponents()
{
	InteractObejct::DisposeComponents();
}

void BaseStone::PreInitialize(const Engine::Modules& modules)
{
	InteractObejct::PreInitialize(modules);
	myManager = Engine::Application::GetGameStateManager();

	auto managerPuzzle_01 = myManager->FindSubManager(L"puzzle_00");
	managerPuzzle_01->Subscribe(L"Data", [this](const std::wstring& name, const std::any& value) 
										{
											DataChangeCallBack(name, value);
										}
	, this);
}


