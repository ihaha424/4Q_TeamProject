#include "pch.h"
#include "Matrix4x4.h"

void Matrix4x4::GetDesc(GE::MATRIX_DESC* pDesc)
{
	memcpy(pDesc, &m[0], sizeof(XMMATRIX));
}

void Matrix4x4::SetDesc(GE::MATRIX_DESC* pDesc)
{
	memcpy(&m[0], pDesc, sizeof(XMMATRIX));
}

void Matrix4x4::Multiply(GE::MATRIX_DESC* in0, GE::MATRIX_DESC* in1, GE::MATRIX_DESC* out)
{
	XMMATRIX m0(in0->m[0]), m1(in1->m[0]);
	memcpy(out, &XMMatrixMultiply(m0, m1).r[0], sizeof(XMMATRIX));
}

void Matrix4x4::CreateScaleMatrix(GE::MATRIX_DESC* out, float x, float y, float z)
{
	memcpy(out, &XMMatrixScaling(x, y, z).r[0], sizeof(XMMATRIX));
}

void Matrix4x4::CreateTranslateMatrix(GE::MATRIX_DESC* out, float x, float y, float z)
{
	memcpy(out, &XMMatrixTranslation(x, y, z).r[0], sizeof(XMMATRIX));
}

void Matrix4x4::CreateRotationMatrix(GE::MATRIX_DESC* out, float x, float y, float z)
{
	memcpy(out, &XMMatrixRotationQuaternion(Quaternion::CreateFromYawPitchRoll(x, y, z)).r[0], sizeof(XMMATRIX));
}

void Matrix4x4::Release()
{
	delete this;
}