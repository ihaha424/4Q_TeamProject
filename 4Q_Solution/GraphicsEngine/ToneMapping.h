#pragma once
#include "Base.h"

class ToneMapping : public Base
{
public:
	explicit ToneMapping() = default;
	virtual ~ToneMapping() = default;

	// Base을(를) 통해 상속됨
	void Free() override;
};

