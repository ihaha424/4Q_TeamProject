#pragma once
#include "Base.h"

class PostProcess : public Base
{
public:
	explicit PostProcess() = default;
	virtual ~PostProcess() = default;

public:
	void Render();

private:
	// Base을(를) 통해 상속됨
	void Free() override;
};

