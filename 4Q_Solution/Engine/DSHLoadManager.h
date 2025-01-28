#pragma once
#include "ConfigData.h"

namespace Engine::DSHLoad
{
	class Manager final : public Load::Manager
	{
	public:
		void Initialize(std::filesystem::path path) override;
		void Finalize() override;

		Load::ConfigData GetGameConfigData() override;

		std::optional<Load::ConfigData> GetWorldConfigData(std::wstring name) override;
		std::optional<Load::ConfigData> GetObjectConfigData(std::wstring name) override;
		std::optional<Load::ConfigData> GetComponentConfigData(std::wstring name) override;

	private:
		Load::ConfigData::Data _gameConfigData;
		std::unordered_map<std::wstring, Load::ConfigData::Data> _worldConfigData;
		std::unordered_map<std::wstring, Load::ConfigData::Data> _objectConfigData;
		std::unordered_map<std::wstring, Load::ConfigData::Data> _componentConfigData;
	};
}
