#pragma once

namespace Engine::Load
{
	struct IManager
	{
		IManager() = default;
		IManager(const IManager& other) = default;
		IManager(IManager&& other) noexcept = default;
		IManager& operator=(const IManager& other) = default;
		IManager& operator=(IManager&& other) noexcept = default;
		virtual ~IManager() = default;

		virtual std::optional<ConfigData> GetWorldConfigData(std::wstring name) = 0;
		virtual std::optional<ConfigData> GetObjectConfigData(std::wstring name) = 0;
		virtual std::optional<ConfigData> GetComponentConfigData(std::wstring name) = 0;
	};

	struct Manager : IManager
	{
		virtual void Initialize(std::filesystem::path path) = 0;
		virtual void Finalize() = 0;

		virtual ConfigData GetGameConfigData() = 0;
	};
}
