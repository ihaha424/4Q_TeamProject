#include "pch.h"
#include "Filter.h"

Filter::Filter()
{
	_pDeviceContext = g_pGraphicDevice->GetDeviceContext();
}
