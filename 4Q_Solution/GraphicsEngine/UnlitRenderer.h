#pragma once
#include "Component.h"
#include "includes/IUnlitRenderer.h"

class UnlitRenderer : public Component, public GE::IUnlitRenderer
{

public:
	virtual void Render() = 0;
};