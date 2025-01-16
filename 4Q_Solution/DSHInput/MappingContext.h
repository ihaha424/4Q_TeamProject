#pragma once

namespace DSH::Input
{
	class Action;

	class MappingContext final : public IMappingContext
	{
	public:
		MappingContext();
		~MappingContext() override;

		HRESULT QueryInterface(const IID& riid, void** ppvObject) override;
		ULONG AddRef() override;
		ULONG Release() override;

		void Update(float deltaTime) override;
		void Reset() override;

		HRESULT GetAction(const wchar_t* name, IAction** ppAction) override;

	private:
		ULONG _referenceCount;

		std::unordered_map<std::wstring, Action*> _actions;
	};
}
