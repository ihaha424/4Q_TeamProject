#pragma once

namespace DSH::Window
{
	class System final :
		public ISystem
	{
	public:
		System();

		HRESULT QueryInterface(const IID& riid, void** ppvObject) override;
		ULONG AddRef() override;
		ULONG Release() override;

		HRESULT CreateClass(HINSTANCE hInstance, LPCWSTR szName, IClass** ppClass) const override;

	private:
		ULONG _referenceCount;
	};
}
