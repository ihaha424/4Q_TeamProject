#pragma once

namespace Engine::Utility
{
	template <typename T>
	concept can_finalize = requires(T object)
	{
		{ object.Finalize() } -> std::convertible_to<void>;
	};
	struct SafeFinalize
	{
		void operator()(can_finalize auto& object) const;
	};

	void SafeFinalize::operator()(can_finalize auto& object) const
	{
		object.Finalize();
	}
}
