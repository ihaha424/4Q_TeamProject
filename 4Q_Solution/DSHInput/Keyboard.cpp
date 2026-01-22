#include "pch.h"
#include "Keyboard.h"

#include "ButtonComponent.h"

DSH::Input::Device::Keyboard::Keyboard() :
	_referenceCount(1)
{
}

DSH::Input::Device::Keyboard::~Keyboard()
{
	std::ranges::for_each(_keys | std::views::values, [](Component::ButtonComponent* key) { key->Release(); });
	_keys.clear();
}

HRESULT DSH::Input::Device::Keyboard::QueryInterface(const IID& riid, void** ppvObject)
{
	if (ppvObject == nullptr) return E_INVALIDARG;
	if (riid != IID_IKeyboard &&
		riid != IID_IDevice &&
		riid != IID_IUnknown) return E_NOINTERFACE;
	*ppvObject = this;
	return S_OK;
}

ULONG DSH::Input::Device::Keyboard::AddRef()
{
	return InterlockedIncrement(&_referenceCount);
}

ULONG DSH::Input::Device::Keyboard::Release()
{
	const ULONG newRefCount = InterlockedDecrement(&_referenceCount);
	if (newRefCount == 0) delete this;
	return newRefCount;
}

void DSH::Input::Device::Keyboard::Update()
{
	std::ranges::for_each(_keys, [](const std::pair<const Key, Component::ButtonComponent*>& keyPair) { keyPair.second->SetValue(GetAsyncKeyState(static_cast<unsigned char>(keyPair.first)) & 0x8000); });
}

void DSH::Input::Device::Keyboard::Reset()
{
	std::ranges::for_each(_keys | std::views::values, [](Component::ButtonComponent* key) { key->Reset(); });
}

HRESULT DSH::Input::Device::Keyboard::GetComponent(const Key key, Component::IButtonComponent** ppComponent)
{
	if (key == Key::Max) return E_INVALIDARG;
	if (ppComponent == nullptr) return E_INVALIDARG;
	Component::ButtonComponent* pButtonComponent = nullptr;
	if (_keys.contains(key) == false)
	{
		pButtonComponent = new Component::ButtonComponent();
		if (pButtonComponent == nullptr) return E_OUTOFMEMORY;
		_keys[key] = pButtonComponent;
	}
	else pButtonComponent = _keys[key];
	pButtonComponent->AddRef();
	*ppComponent = pButtonComponent;
	return S_OK;
}
