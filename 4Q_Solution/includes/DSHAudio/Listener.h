#pragma once

namespace DSH::Audio
{
	class Listener final : public IListener
	{
	public:
		Listener(FMOD::System* system, int index);

		HRESULT QueryInterface(const IID& riid, void** ppvObject) override;
		ULONG AddRef() override;
		ULONG Release() override;

		HRESULT Activate() override;

		HRESULT SetPosition(const Vector& position) override;
		HRESULT SetVelocity(const Vector& velocity) override;
		HRESULT SetForward(const Vector& forward) override;
		HRESULT SetUp(const Vector& up) override;


	private:
		ULONG _referenceCount;

		FMOD::System* _system;

		Vector _position;
		Vector _velocity;
		Vector _forward;
		Vector _up;

		int _index;
	};
}
