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

void Engine::DSHLoad::Manager::LoadRegisterData(const std::filesystem::path& path)
{
	for (nlohmann::json data = nlohmann::json::parse(std::ifstream(path)); const auto& objectData: data["registInfo"]["regists"])
	{
		std::string objectClassNameData = objectData["className"].get<std::string>();
		std::wstring objectClassName;
		objectClassName.assign(objectClassNameData.begin(), objectClassNameData.end());
		std::string fbxPathData = objectData["fbxPath"].get<std::string>();
		std::filesystem::path fbxPath(fbxPathData);
		_objectRegisterData[objectClassName][L"fbxPath"] = fbxPath;
	}
}

void Engine::DSHLoad::Manager::LoadCloneData(const std::filesystem::path& path)
{
	for (nlohmann::json data = nlohmann::json::parse(std::ifstream(path)); const auto& objectData : data["objectGroup"]["groups"])
	{
		for (const auto& modelData : objectData["models"])
		{
			std::string objectClassNameData = modelData["className"].get<std::string>();
			std::wstring objectClassName;
			objectClassName.assign(objectClassNameData.begin(), objectClassNameData.end());

			bool isPublic = modelData["publicObject"].get<bool>();
			bool hasMesh = modelData["meshObject"].get<bool>();
			bool isDynamic = modelData["dynamicObject"].get<bool>();

			const auto& position = modelData["transformData"]["position"];
			Math::Vector3 positionData = { position["x"].get<float>(), position["y"].get<float>(), position["z"].get<float>() };

			const auto& rotation = modelData["transformData"]["rotation"];
			Math::Quaternion rotationData = { rotation["x"].get<float>(), rotation["y"].get<float>(), rotation["z"].get<float>(), rotation["w"].get<float>() };

			const auto& scale = modelData["transformData"]["scale"];
			Math::Vector3 scaleData = { scale["x"].get<float>(), scale["y"].get<float>(), scale["z"].get<float>() };

			const auto& boxscale = modelData["boxScale"];
			Math::Vector3 boxScaleData = { boxscale["x"].get<float>(), boxscale["y"].get<float>(), boxscale["z"].get<float>() };

			const auto& boxPosition = modelData["boxPosition"];
			Math::Vector3 boxPositionData = { boxPosition["x"].get<float>(), boxPosition["y"].get<float>(), boxPosition["z"].get<float>() };
			
			bool isSphere = modelData["isSphere"];

			positionData *= 10;
			scaleData /= 10;
			boxScaleData = boxScaleData.Split(scaleData) * 50.f;


			//boxScaleData *= 10;
			//boxPositionData *= 10;
			boxPositionData = Math::Vector3::Zero;
			//boxPositionData /= 10;

			Properties cloneData
			{
				std::pair<const std::wstring, std::any>{L"isPublic", isPublic},
				std::pair<const std::wstring, std::any>{L"hasMesh", hasMesh},
				std::pair<const std::wstring, std::any>{L"isDynamic", isDynamic},
				std::pair<const std::wstring, std::any>{L"position", positionData},
				std::pair<const std::wstring, std::any>{L"rotation", rotationData},
				std::pair<const std::wstring, std::any>{L"scale", scaleData},
				std::pair<const std::wstring, std::any>{L"boxScale", boxScaleData},
				std::pair<const std::wstring, std::any>{L"boxPosition", boxPositionData},
				std::pair<const std::wstring, std::any>{L"isSphere", isSphere}
			};
			_objectCloneData[objectClassName].push_back(cloneData);
		}
	}
}

std::optional<Engine::Load::ConfigData> Engine::DSHLoad::Manager::GetObjectRegisterData(const std::wstring& name)
{
	if (const auto configData = _objectRegisterData.find(name); configData == _objectRegisterData.end())
		return std::nullopt;
	else return Load::ConfigData(&configData->second);
}

std::vector<Engine::Load::ConfigData> Engine::DSHLoad::Manager::GetObjectCloneData(const std::wstring& name)
{
	std::vector<Load::ConfigData> result;
	if (const auto configData = _objectCloneData.find(name); configData != _objectCloneData.end())
	{
		for (auto& data : configData->second)
		{
			result.emplace_back(&data);
		}
	}
	return result;
}

