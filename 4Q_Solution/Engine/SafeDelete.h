#pragma once

namespace Engine::Utility
{
	struct SafeDelete
	{
		template <class T>
		void operator()(T** instance) const;
	};

	template <class T>
	void SafeDelete::operator()(T** instance) const
	{
		if (instance == nullptr ||
			*instance == nullptr) return;
		delete *instance;
		*instance = nullptr;
	}
}

