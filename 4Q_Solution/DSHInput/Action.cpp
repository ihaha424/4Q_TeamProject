#include "pch.h"
#include "Action.h"

#include "ChordAction.h"
#include "Down.h"

DSH::Input::Action::Action() :
	_referenceCount(1),
	_isTriggered(false),
	_event(Trigger::Event::Completed),
	_value{}
{
}

DSH::Input::Action::~Action()
{
	for (auto& down : _downs)
	{
		down->Release();
		down = nullptr;
	}
	_downs.clear();

	for (auto& chordAction : _chordActions)
	{
		chordAction->Release();
		chordAction = nullptr;
	}
	_chordActions.clear();
}

HRESULT DSH::Input::Action::QueryInterface(const IID& riid, void** ppvObject)
{
	if (ppvObject == nullptr) return E_INVALIDARG;
	if (riid != IID_IAction &&
		riid != IID_IUnknown) return E_NOINTERFACE;
	*ppvObject = this;
	return S_OK;
}

ULONG DSH::Input::Action::AddRef()
{
	return InterlockedIncrement(&_referenceCount);
}

ULONG DSH::Input::Action::Release()
{
	const ULONG newRefCount = InterlockedDecrement(&_referenceCount);
	if (newRefCount == 0) delete this;
	return newRefCount;
}

void DSH::Input::Action::Update(float deltaTime)
{
	std::ranges::for_each(_downs, [](Trigger::Down* down) { down->Update(); });
	std::ranges::for_each(_chordActions, [](Trigger::ChordAction* chordAction) { chordAction->Update(); });
	if (_isTriggered && _listeners.contains(_event)) std::ranges::for_each(_listeners[_event], [this](const Listener& listener) {listener(_value); });
}

void DSH::Input::Action::Reset()
{
	_value = Value::Zero();
	_event = Trigger::Event::Completed;
	_isTriggered = false;
}

void DSH::Input::Action::AddListener(const Trigger::Event event, const Listener listener)
{
	_listeners[event].push_back(listener);
}

HRESULT DSH::Input::Action::GetTrigger(Trigger::IDown** ppDown)
{
	if (ppDown == nullptr) return E_INVALIDARG;
	Trigger::Down* pDown = new Trigger::Down();
	if (pDown == nullptr) return E_OUTOFMEMORY;
	pDown->BindOnTriggered([this](const Trigger::Event event, const Value value) {OnTriggered(event, value); });
	_downs.push_back(pDown);
	pDown->AddRef();
	*ppDown = pDown;
	return S_OK;
}

HRESULT DSH::Input::Action::GetTrigger(Trigger::IChordAction** ppChordAction)
{
	if (ppChordAction == nullptr) return E_INVALIDARG;
	Trigger::ChordAction* pChordAction = new Trigger::ChordAction();
	if (pChordAction == nullptr) return E_OUTOFMEMORY;
	pChordAction->BindOnTriggered([this](const Trigger::Event event, const Value value) {OnTriggered(event, value); });
	_chordActions.push_back(pChordAction);
	pChordAction->AddRef();
	*ppChordAction = pChordAction;
	return S_OK;
}

bool DSH::Input::Action::IsTriggered()
{
	return _isTriggered;
}

void DSH::Input::Action::OnTriggered(const Trigger::Event event, const Value value)
{
	_event = (std::max)(_event, event);
	_value += value;
	_isTriggered = true;
}
