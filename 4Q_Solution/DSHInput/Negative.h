#pragma once

namespace DSH::Input::Modifier
{
	class Negative final : public INegative
	{
	public:
		Negative();

		HRESULT QueryInterface(const IID& riid, void** ppvObject) override;
		ULONG AddRef() override;
		ULONG Release() override;

		Value Modify(Value value) const override;

	private:
		ULONG _referenceCount;
	};
}
