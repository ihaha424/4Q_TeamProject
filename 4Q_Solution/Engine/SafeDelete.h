#pragma once

namespace Engine::Utility
{
	struct SafeDelete
	{
		template <typename T>
		void operator()(T** instance) const;

		template <typename T>
		void operator()(T* instance) const;
	};

	template <typename T>
	void SafeDelete::operator()(T** instance) const
	{
		if (instance == nullptr ||
			*instance == nullptr) return;
		delete* instance;
		*instance = nullptr;
	}

	template <typename T>
	void SafeDelete::operator()(T* instance) const
	{
		if (instance == nullptr) return;
		delete instance;
	}
}

