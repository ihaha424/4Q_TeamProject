#include "pch.h"
#include "DSHLoadManager.h"

void Engine::DSHLoad::Manager::Initialize()
{
	// TODO: Implement this.
}

void Engine::DSHLoad::Manager::Finalize()
{
	// TODO: Implement this.
}

void Engine::DSHLoad::Manager::LoadGameData(std::filesystem::path path)
{
	// TODO: Implement this.
}

Engine::Load::ConfigData Engine::DSHLoad::Manager::GetGameConfigData()
{
	return Load::ConfigData(&_gameConfigData);
}

std::optional<Engine::Load::ConfigData> Engine::DSHLoad::Manager::GetWorldConfigData(const std::wstring name)
{
	if (const auto configData = _worldConfigData.find(name); configData == _worldConfigData.end())
		return std::nullopt;
	else return Load::ConfigData(&configData->second);
}
