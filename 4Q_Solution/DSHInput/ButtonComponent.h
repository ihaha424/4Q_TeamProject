#pragma once

namespace DSH::Input::Component
{
	class ButtonComponent final : public IButtonComponent
	{
	public:
		ButtonComponent();

		HRESULT QueryInterface(const IID& riid, void** ppvObject) override;
		ULONG AddRef() override;
		ULONG Release() override;

		[[nodiscard]] Value GetValue() const override;
		void Reset();

		void SetValue(bool value);

	private:
		ULONG _referenceCount;

		bool _value;
	};
}
