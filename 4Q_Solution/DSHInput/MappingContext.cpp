#include "pch.h"
#include "MappingContext.h"

#include "Action.h"

DSH::Input::MappingContext::MappingContext() :
	_referenceCount(1)
{
}

DSH::Input::MappingContext::~MappingContext()
{
	for (auto& action : _actions | std::views::values)
	{
		action->Release();
		action = nullptr;
	}
	_actions.clear();
}

HRESULT DSH::Input::MappingContext::QueryInterface(const IID& riid, void** ppvObject)
{
	if (ppvObject == nullptr) return E_INVALIDARG;
	if (riid != IID_IMappingContext &&
		riid != IID_IUnknown) return E_NOINTERFACE;
	*ppvObject = this;
	return S_OK;
}

ULONG DSH::Input::MappingContext::AddRef()
{
	return InterlockedIncrement(&_referenceCount);
}

ULONG DSH::Input::MappingContext::Release()
{
	const ULONG newRefCount = InterlockedDecrement(&_referenceCount);
	if (newRefCount == 0) delete this;
	return newRefCount;
}

void DSH::Input::MappingContext::Update(float deltaTime)
{
	std::ranges::for_each(_actions | std::views::values , [deltaTime](Action* action) { action->Update(deltaTime); });
}

void DSH::Input::MappingContext::Reset()
{
	std::ranges::for_each(_actions | std::views::values, [](Action* action) { action->Reset(); });
}

HRESULT DSH::Input::MappingContext::GetAction(const wchar_t* name, IAction** ppAction)
{
	if (name == nullptr) return E_INVALIDARG;
	if (ppAction == nullptr) return E_INVALIDARG;
	Action* pAction = nullptr;
	if (_actions.contains(name) == false)
	{
		pAction = new Action();
		if (pAction == nullptr) return E_OUTOFMEMORY;
		_actions[name] = pAction;
	}
	else pAction = _actions[name];
	pAction->AddRef();
	*ppAction = pAction;
	return S_OK;
}
