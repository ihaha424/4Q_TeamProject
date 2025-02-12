#include "pch.h"
#include "PuzzleManager.h"
#include "Application.h"

PuzzleManager::PuzzleManager()
	: _sync{ nullptr }
{
}

void PuzzleManager::Prepare(Engine::Content::Factory::Component* componentFactory)
{
	_sync = componentFactory->Clone<Engine::Component::Synchronize>(this);
}

void PuzzleManager::DisposeComponents()
{
	Engine::Object::Dispose();
	_sync->Dispose();
}

void PuzzleManager::PreInitialize(const Engine::Modules& modules)
{
	Engine::Object::PreInitialize(modules);
	_sync->AddCallback((short)PacketID::PuzzleStart, &PuzzleManager::SetStart, this);
	_sync->AddCallback((short)PacketID::PuzzleSuccess, &PuzzleManager::SetFinish, this);
	_sync->AddCallback((short)PacketID::InteractObject, &PuzzleManager::SetInteract, this);
}

void PuzzleManager::PostInitialize(const Engine::Modules& modules)
{
	Engine::Object::PostInitialize(modules);
	myManager->Subscribe(L"Data", [this](const std::wstring& name, const std::any& value)
		{
			DataChangeCallBack(name, value);
		}
	, this);
}
