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

		[[nodiscard]] bool IsDown() const override;
		[[nodiscard]] bool IsUp() const override;
		[[nodiscard]] bool IsPressed() const override;
		[[nodiscard]] bool IsReleased() const override;

	private:
		ULONG _referenceCount;

		bool _value;
		bool _previousValue;
	};
}
