#pragma once

namespace Engine::Load
{
	class ConfigData
	{
	public:
		using Data = std::unordered_map<std::wstring, std::any>;

		explicit ConfigData(Data* data) : _data(data) {}

		template<typename T>
		std::optional<T> GetProperty(const std::wstring& propertyName) const
		{
			if (const auto data = _data->find(propertyName); data != _data->end())
			{
				try
				{
					return std::any_cast<T>(data->second);
				}
				catch (const std::bad_any_cast&)
				{
					return std::nullopt;
				}
			}
			return std::nullopt;
		}
	private:
		Data* _data;
	};
}
