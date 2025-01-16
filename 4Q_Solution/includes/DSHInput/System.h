#pragma once

namespace DSH::Input
{
	class System final :
		public ISystem
	{
	public:
		System();

		HRESULT QueryInterface(const IID& riid, void** ppvObject) override;
		ULONG AddRef() override;
		ULONG Release() override;

		HRESULT CreateKeyboard(Device::IKeyboard** ppKeyboard) const override;
		HRESULT CreateMouse(Device::IMouse** ppMouse) const override;
		HRESULT CreateController(Device::IController** ppController) const override;
		HRESULT CreateMappingContext(IMappingContext** ppMappingContext) const override;
		HRESULT CreateModifier(Modifier::INegative** ppModifier) const override;
		HRESULT CreateModifier(Modifier::ISwizzleAxis** ppModifier) const override;

	private:
		ULONG _referenceCount;
	};
}
