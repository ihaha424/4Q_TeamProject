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
	const std::list<RenderData>& GetRenderData(const unsigned int layer) { return _datas[layer]; }
	const std::list<RenderData>* GetRenderDatas() { return _datas; }
	const unsigned int GetMaxLayer() const { return _maxLayer; }

public:
	void Initialize(const unsigned int maxLayer);
	void RegisterRenderQueue(const unsigned int layer, GE::IMeshRenderer* pMeshRenderer, Matrix* pMatrix);
	void UnRegisterRenderQueue(const unsigned int layer, GE::IMeshRenderer* pMeshRenderer);

private:
	// Base을(를) 통해 상속됨
	void Free() override;

private:
	std::list<RenderData>* _datas;
	unsigned int _maxLayer{ 0 };
};