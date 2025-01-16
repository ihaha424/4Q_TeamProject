#pragma once

namespace DSH::Time
{
	class System final :
		public ISystem
	{
    public:
        System();

        HRESULT QueryInterface(const IID& riid, void** ppvObject) override;
        ULONG AddRef() override;
        ULONG Release() override;

        HRESULT CreateTickTimer(ITickTimer** ppTickTimer) const override;

    private:
        ULONG _referenceCount;
	};
}