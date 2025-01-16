#pragma once
#include "IAxisComponent.h"

namespace DSH::Input::Component
{
	class AxisComponent final : public IAxisComponent
	{
	public:
		AxisComponent();

		HRESULT QueryInterface(const IID& riid, void** ppvObject) override;
		ULONG AddRef() override;
		ULONG Release() override;

		[[nodiscard]] Value GetValue() const override;
		void Reset();

		void SetRelativeValue(LONG value);
		void SetAbsoluteValue(LONG value);

		void SetDeadZone(LONG deadZone);
		void SetSensitivity(LONG sensitivity);

	private:
		ULONG _referenceCount;

		LONG _value;
		LONG _sensitivity;
		LONG _deadZone;

		LONG _absoluteValue;
	};
}
