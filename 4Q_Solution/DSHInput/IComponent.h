#pragma once

namespace DSH::Input
{
	union Value;
	namespace Component
	{
		EXTERN_C const IID IID_IComponent;

		EXTERN_C MIDL_INTERFACE("e43df238-7c9f-4abf-911b-ed188143012e")
			DSH_INPUT_LIBRARY_API IComponent : IUnknown
		{
			IComponent() = default;
			IComponent(const IComponent& other) = default;
			IComponent(IComponent&& other) noexcept = default;
			IComponent& operator=(const IComponent& other) = default;
			IComponent& operator=(IComponent&& other) noexcept = default;
			virtual ~IComponent() = default;

			[[nodiscard]] virtual Value STDMETHODCALLTYPE GetValue() const = 0;
		};
	}
}
