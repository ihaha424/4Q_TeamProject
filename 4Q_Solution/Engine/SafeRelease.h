#pragma once

namespace Engine::Utility
{
	template <class T>
	concept can_release_ref_count = requires(T com)
	{
		{ com.Release() } -> std::convertible_to<ULONG>;
	};

	template <class T>
	concept can_release = requires(T com)
	{
		{ com.Release() } -> std::convertible_to<void>;
	};

	struct SafeRelease
	{
		void operator()(can_release auto** object) const;

		ULONG operator()(can_release_ref_count auto** object) const;

		void operator()(can_release_ref_count auto** object, char const* message) const;
	};

	void SafeRelease::operator()(can_release auto** object) const
	{
		if (object == nullptr ||
			*object == nullptr) return;
		(*object)->Release();
		*object = nullptr;
	}

	ULONG SafeRelease::operator()(can_release_ref_count auto** object) const
	{
		if (object == nullptr ||
			*object == nullptr) return 0;
		const ULONG refCount = (*object)->Release();
		(*object) = nullptr;
		return refCount;
	}

	void SafeRelease::operator()(can_release_ref_count auto** object, char const* message) const
	{
		if (operator()(object) != 0) throw std::exception(message);
	}
}

