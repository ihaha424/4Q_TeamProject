#include "pch.h"
#include "ChordAction.h"

#include "Value.h"

DSH::Input::Trigger::ChordAction::ChordAction() :
_referenceCount(1), _component(nullptr), _precedingAction(nullptr), _isDown(false)
{
}

DSH::Input::Trigger::ChordAction::~ChordAction()
{
	if (_component != nullptr)
	{
		_component->Release();
		_component = nullptr;
	}

	if (_precedingAction != nullptr)
	{
		_precedingAction->Release();
		_precedingAction = nullptr;
	}

	std::ranges::for_each(_modifiers, [](Modifier::IModifier* modifier)
		{
			modifier->Release();
			modifier = nullptr;
		});
	_modifiers.clear();
}

HRESULT DSH::Input::Trigger::ChordAction::QueryInterface(const IID& riid, void** ppvObject)
{
	if (ppvObject == nullptr) return E_INVALIDARG;
	if (riid != IID_IChordAction &&
		riid != IID_ITrigger &&
		riid != IID_IUnknown) return E_NOINTERFACE;
	*ppvObject = this;
	return S_OK;
}

ULONG DSH::Input::Trigger::ChordAction::AddRef()
{
	return InterlockedIncrement(&_referenceCount);
}

ULONG DSH::Input::Trigger::ChordAction::Release()
{
	const ULONG newRefCount = InterlockedDecrement(&_referenceCount);
	if (newRefCount == 0) delete this;
	return newRefCount;
}

void DSH::Input::Trigger::ChordAction::SetComponent(Component::IComponent* component)
{
	if (_component != nullptr) _component->Release();
	if (component != nullptr) component->AddRef();
	_component = component;
}

void DSH::Input::Trigger::ChordAction::AddModifier(Modifier::IModifier* modifier)
{
	modifier->AddRef();
	_modifiers.push_back(modifier);
}

void DSH::Input::Trigger::ChordAction::Update()
{
	if (_component == nullptr) return;
	if (_precedingAction == nullptr) return;
	if (_precedingAction->IsTriggered() == false)
	{
		return;
	}

	const Value value = std::accumulate(_modifiers.begin(), _modifiers.end(), _component->GetValue(),
		[](const Value v, const Modifier::IModifier* modifier)
		{
			return modifier->Modify(v);
		});
	const bool isDown = value != Value::Zero();
	if (isDown && !_isDown)
	{
		_onTriggered(Event::Started, value);
	}
	else if (isDown && _isDown)
	{
		_onTriggered(Event::Triggered, value);
	}
	else if (!isDown && _isDown) _onTriggered(Event::Completed, value);
	_isDown = isDown;
}

void DSH::Input::Trigger::ChordAction::BindOnTriggered(const OnTriggered& onTriggered)
{
	_onTriggered = onTriggered;
}

void DSH::Input::Trigger::ChordAction::SetPrecedingAction(IAction* precedingAction)
{
	if (_precedingAction != nullptr) _precedingAction->Release();
	if (precedingAction != nullptr) precedingAction->AddRef();
	_precedingAction = precedingAction;
}
