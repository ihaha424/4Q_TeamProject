#include "pch.h"
#include "Down.h"

#include "Value.h"

DSH::Input::Trigger::Down::Down() :
	_referenceCount(1), _component(nullptr), _isDown(false)
{
}

DSH::Input::Trigger::Down::~Down()
{
	if (_component != nullptr)
	{
		_component->Release();
		_component = nullptr;
	}
	std::ranges::for_each(_modifiers, [](Modifier::IModifier* modifier)
	{
		modifier->Release();
		modifier = nullptr;
	});
	_modifiers.clear();
}

HRESULT DSH::Input::Trigger::Down::QueryInterface(const IID& riid, void** ppvObject)
{
	if (ppvObject == nullptr) return E_INVALIDARG;
	if (riid != IID_IDown &&
		riid != IID_ITrigger &&
		riid != IID_IUnknown) return E_NOINTERFACE;
	*ppvObject = this;
	return S_OK;
}

ULONG DSH::Input::Trigger::Down::AddRef()
{
	return InterlockedIncrement(&_referenceCount);
}

ULONG DSH::Input::Trigger::Down::Release()
{
	const ULONG newRefCount = InterlockedDecrement(&_referenceCount);
	if (newRefCount == 0) delete this;
	return newRefCount;
}

void DSH::Input::Trigger::Down::Update()
{
	if (_component == nullptr) return;

	const Value value = std::accumulate(_modifiers.begin(), _modifiers.end(), _component->GetValue(),
		[](const Value v, const Modifier::IModifier* modifier) {return modifier->Modify(v); });
	const bool isDown = value != Value::Zero();
	if (isDown && !_isDown) _onTriggered(Event::Started, value);
	else if (isDown && _isDown) _onTriggered(Event::Triggered, value);
	else if (!isDown && _isDown) _onTriggered(Event::Completed, value);
	_isDown = isDown;
}

void DSH::Input::Trigger::Down::BindOnTriggered(const std::function<void(Event, Value)>& onTriggered)
{
	_onTriggered = onTriggered;
}

void DSH::Input::Trigger::Down::SetComponent(Component::IComponent* component)
{
	if (_component != nullptr) _component->Release();
	if (component != nullptr) component->AddRef();
	_component = component;
}

void DSH::Input::Trigger::Down::AddModifier(Modifier::IModifier* modifier)
{
	modifier->AddRef();
	_modifiers.push_back(modifier);
}