#pragma once
#include "Base.h"

namespace GE
{
	class IMeshRenderer;
}

class MeshRenderer;
class RenderGroup : public Base
{
	using RenderData = std::pair<MeshRenderer*, Matrix*>;
public:
	explicit RenderGroup() = default;
	virtual ~RenderGroup() = default;

public:
	const std::list<RenderData>& GetRenderDatas() { return _datas; }

public:
	void RegisterRenderQueue(GE::IMeshRenderer* pMeshRenderer, Matrix* pMatrix);
	void UnRegisterRenderQueue(GE::IMeshRenderer* pMeshRenderer);

private:
	// Base을(를) 통해 상속됨
	void Free() override;

private:
	std::list<RenderData> _datas;
};