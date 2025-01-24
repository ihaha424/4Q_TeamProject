#include "pch.h"
#include "MeshRenderer.h"
#include "VertexShader.h"

void MeshRenderer::SetVertexShader()
{
	_vertexShader->SetVertexShader();
}

void MeshRenderer::Release()
{
	delete this;
}

void MeshRenderer::SetRenderLayer(const unsigned int layer)
{
	_layer = layer;
}
