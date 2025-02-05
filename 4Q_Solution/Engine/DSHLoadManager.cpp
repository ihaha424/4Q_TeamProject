#include "pch.h"
#include "DSHLoadManager.h"

void Engine::DSHLoad::Manager::Initialize()
{
}

void Engine::DSHLoad::Manager::Finalize()
{
}

Engine::Load::ConfigData Engine::DSHLoad::Manager::GetGameConfigData()
{
	return Load::ConfigData(&_gameConfigData);
}

void Engine::DSHLoad::Manager::LoadMapData(const std::filesystem::path path)
{
	std::ifstream file(path);
	nlohmann::json data = nlohmann::json::parse(file);
	const auto& registerData = data["registInfo"]["regists"];
	for (const auto& objectData: registerData)
	{
		std::string objectClassNameData = objectData["className"].get<std::string>();
		std::wstring objectClassName;
		objectClassName.assign(objectClassNameData.begin(), objectClassNameData.end());
		std::string fbxPathData = objectData["fbxPath"].get<std::string>();
		std::filesystem::path fbxPath(fbxPathData);
		_objectRegisterData[objectClassName][L"fbxPath"] = fbxPath;
	}
}

std::optional<Engine::Load::ConfigData> Engine::DSHLoad::Manager::GetObjectRegisterData(const std::wstring name)
{
	if (const auto configData = _objectRegisterData.find(name); configData == _objectRegisterData.end())
		return std::nullopt;
	else return Load::ConfigData(&configData->second);
}