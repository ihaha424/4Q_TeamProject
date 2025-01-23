#pragma once
#include "ConfigData.h"

namespace Engine::DSHLoad
{
	class Manager final : public Load::Manager
	{
	public:
		void Initialize() override;
		void Finalize() override;

		void LoadGameData(std::filesystem::path path) override;

		Load::ConfigData GetGameConfigData() override;

	private:
		Load::ConfigData::Data _gameConfigData;
	};
}
