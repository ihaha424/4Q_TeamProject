#pragma once

namespace Engine::Utility
{
	template <class T>
	concept CanReleaseRefCount = requires(T com)
	{
		{ com.Release() } -> std::convertible_to<ULONG>;
	};

	template <class T>
	concept CanRelease = requires(T com)
	{
		{ com.Release() } -> std::convertible_to<void>;
	};

	struct SafeRelease
	{
		void operator()(CanRelease auto** object) const;

		ULONG operator()(CanReleaseRefCount auto** object) const;

		void operator()(CanReleaseRefCount auto** object, char const* message) const;
	};

	void SafeRelease::operator()(CanRelease auto** object) const
	{
		if (object == nullptr ||
			*object == nullptr) return;
		(*object)->Release();
		*object = nullptr;
	}

	ULONG SafeRelease::operator()(CanReleaseRefCount auto** object) const
	{
		if (object == nullptr ||
			*object == nullptr) return 0;
		const ULONG refCount = (*object)->Release();
		(*object) = nullptr;
		return refCount;
	}

	void SafeRelease::operator()(CanReleaseRefCount auto** object, char const* message) const
	{
		if (operator()(object) != 0) throw std::exception(message);
	}
}

