#pragma once
#include "DSHAction.h"

namespace Engine::DSHInput
{
	class MappingContext final : public Input::MappingContext
	{
	public:
		MappingContext();

		void Setup(DSH::Input::IMappingContext* mappingContext);

		void Initialize() override;
		void Update(float deltaTime) override;
		void Reset() override;
		void Finalize() override;

		Input::IAction* GetAction(const wchar_t* name) override;

	private:
		DSH::Input::IMappingContext* _mappingContext;

		std::unordered_map<std::wstring, Action> _actions;
	};
}