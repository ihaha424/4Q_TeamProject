#pragma once
#include "includes/ILineRenderer.h"

class VertexShader;
class PixelShader;
class LineRenderer : public GE::ILineRenderer
{
	struct Line
	{
		Vector3 position;
		Vector2 waveData;
	};

public:
	// ILineRenderer을(를) 통해 상속됨
	void Release() override;
	void SetSourcePosition(float* pArray) override;
	void SetDestinationPosition(float* pArray) override;	
	void SetSegment(unsigned int segment) override;

public:
	void Initialize();
	void Update();
	void Render();

private:
	std::shared_ptr<VertexShader> _vs;
	std::shared_ptr<PixelShader> _ps;
	ID3D11DeviceContext* _pDeviceContext{ nullptr };
	ID3D11Buffer* _pVertexBuffer{ nullptr };
	Vector3* _pSrcPosition;
	Vector3* _pDstPosition;
	unsigned int _numSegments{ 0 };
	unsigned int _stride{ 0 };
	unsigned int _offset{ 0 };
};