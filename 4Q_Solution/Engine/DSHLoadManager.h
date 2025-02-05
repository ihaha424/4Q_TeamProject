#pragma once
#include "ConfigData.h"

namespace Engine::DSHLoad
{
	class Manager final : public Load::Manager
	{
		using ClassName = std::wstring;
		using Properties = Load::ConfigData::Data;
	public:
		void Initialize() override;
		void Finalize() override;

		void LoadRegisterData(const std::filesystem::path& path) override;
		void LoadCloneData(const std::filesystem::path& path) override;

		Load::ConfigData GetGameConfigData() override;
		std::optional<Load::ConfigData> GetObjectRegisterData(const std::wstring& name) override;
		std::vector<Load::ConfigData> GetObjectCloneData(const std::wstring& name) override;

	private:
		Load::ConfigData::Data _gameConfigData;
		std::unordered_map<ClassName, Properties> _objectRegisterData;
		std::unordered_map<std::wstring, std::vector<Properties>> _objectCloneData;
	};
}
