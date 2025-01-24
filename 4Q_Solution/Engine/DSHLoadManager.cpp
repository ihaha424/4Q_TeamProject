#include "pch.h"
#include "DSHLoadManager.h"

void Engine::DSHLoad::Manager::Initialize(std::filesystem::path path)
{
	// TODO: Implement this.
}

void Engine::DSHLoad::Manager::Finalize()
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

std::optional<Engine::Load::ConfigData> Engine::DSHLoad::Manager::GetObjectConfigData(const std::wstring name)
{
	if (const auto configData = _objectConfigData.find(name); configData == _objectConfigData.end())
		return std::nullopt;
	else return Load::ConfigData(&configData->second);
}

std::optional<Engine::Load::ConfigData> Engine::DSHLoad::Manager::GetComponentConfigData(const std::wstring name)
{
	if (const auto configData = _componentConfigData.find(name); configData == _componentConfigData.end())
		return std::nullopt;
	else return Load::ConfigData(&configData->second);
}
