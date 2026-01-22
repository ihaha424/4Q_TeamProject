#pragma once

namespace DSH::Input::Modifier
{
	class SwizzleAxis final : public ISwizzleAxis
	{
	public:
		SwizzleAxis();

		HRESULT QueryInterface(const IID& riid, void** ppvObject) override;
		ULONG AddRef() override;
		ULONG Release() override;

		Value Modify(Value value) const override;

		void SetType(Type type) override;

	private:
		ULONG _referenceCount;
		Type _type;
	};
}
