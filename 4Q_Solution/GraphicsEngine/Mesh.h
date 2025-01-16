#pragma once
#include "Base.h"

struct MeshVertex
{
	Vector4 position;
	Vector3 normal;
	Vector3 tangent;
	Vector3 biTangent;
	Vector2 texCoord[2];

	unsigned int blendIndices[4]{};
	float blendWeights[4]{};
};

class VertexShader;
class Material;
class VIBuffer;
class Mesh : public Base
{
	friend class DX11Renderer;
	friend class SkyBoxRenderer;
public:
	explicit Mesh(std::vector<MeshVertex>& vertices, std::vector<unsigned int>& indices);
	virtual ~Mesh() = default;

public:
	const unsigned int GetID() const { return _ID; }

public:
	void SetVertexShader();
	void SetID(unsigned int ID) { _ID = ID; }

public:
	void BindMaterial(Material* pMaterial) { _pMaterial = pMaterial; }
	void BindVertexShader(std::shared_ptr<VertexShader>& vertexShader) { _vertexShader = vertexShader; }

private:
	// Base을(를) 통해 상속됨
	void Free() override;

private:
	std::shared_ptr<VertexShader>	_vertexShader;
	VIBuffer*						_pVIBuffer{ nullptr };
	Material*						_pMaterial{ nullptr };
	unsigned int					_ID{ 0 };
};