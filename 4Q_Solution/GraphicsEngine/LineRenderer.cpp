#include "pch.h"
#include "LineRenderer.h"
#include "VertexShader.h"
#include "PixelShader.h"

void LineRenderer::Release()
{
    SafeRelease(_pVertexBuffer);
	delete this;
}

void LineRenderer::SetSourcePosition(float* pArray)
{
    _pSrcPosition = reinterpret_cast<Vector3*>(pArray);
}

void LineRenderer::SetDestinationPosition(float* pArray)
{
    _pDstPosition = reinterpret_cast<Vector3*>(pArray);
}

void LineRenderer::SetSegment(unsigned int segment)
{
    _numSegments = segment;
}

void LineRenderer::Initialize()
{       
    std::vector<Line> lineVertices;
    lineVertices.resize(_numSegments + 1);

    D3D11_BUFFER_DESC bufferDesc = {};
    bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    bufferDesc.ByteWidth = lineVertices.size() * sizeof(Line);
    bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    D3D11_SUBRESOURCE_DATA initData = {};
    initData.pSysMem = lineVertices.data();

    ID3D11Device* pDevice = g_pGraphicDevice->GetDevice();
    pDevice->CreateBuffer(&bufferDesc, &initData, &_pVertexBuffer);

    _stride = sizeof(Line);
}

void LineRenderer::Update()
{
    ID3D11DeviceContext* pDeviceContext = g_pGraphicDevice->GetDeviceContext();
    D3D11_MAPPED_SUBRESOURCE mappedResource;
    HRESULT hr = pDeviceContext->Map(_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);    

    Line* vertices = reinterpret_cast<Line*>(mappedResource.pData);
    for (unsigned int i = 0; i <= _numSegments; ++i)
    {
        float t = (float)i / _numSegments;
        vertices[i].position = XMVectorLerp(*_pSrcPosition, *_pDstPosition, t);
        vertices[i].waveData = Vector2(t, i % 2 == 0 ? 1.0f : -1.0f);
    }

    pDeviceContext->Unmap(_pVertexBuffer, 0);
}

void LineRenderer::Render()
{    
    _vs->SetVertexShader();
    _ps->SetPixelShader();

    _pDeviceContext->IASetVertexBuffers(0, 1, &_pVertexBuffer, &_stride, &_offset);
    _pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
    _pDeviceContext->Draw(_numSegments + 1, 0);
}
