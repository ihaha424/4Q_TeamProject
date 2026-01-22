#pragma once

namespace Engine::Input
{
	struct IAction;
	struct IMappingContext
	{
		IMappingContext() = default;
		IMappingContext(const IMappingContext& other) = default;
		IMappingContext(IMappingContext&& other) noexcept = default;
		IMappingContext& operator=(const IMappingContext& other) = default;
		IMappingContext& operator=(IMappingContext&& other) noexcept = default;
		virtual ~IMappingContext() = default;

		virtual void GetAction(const wchar_t* name, IAction** action) = 0;
	};

	struct MappingContext : IMappingContext
	{
		virtual void Initialize() = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void Reset() = 0;
		virtual void Finalize() = 0;
	};
}