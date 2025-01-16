#include "pch.h"
#include "Functions.h"

#include "System.h"

HRESULT DSH::Time::CreateSystem::operator()(ISystem** ppSystem) const
{
	if (ppSystem == nullptr) return E_INVALIDARG;
	System* pSystem = new System();
	if (pSystem == nullptr) return E_OUTOFMEMORY;
	*ppSystem = pSystem;
	return S_OK;
}
