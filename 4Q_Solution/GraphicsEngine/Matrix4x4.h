#pragma once
#include "includes/IMatrix.h"

class Matrix4x4 : public GE::IMatrix, public Matrix
{
public:
	explicit Matrix4x4() = default;
	virtual ~Matrix4x4() = default;

	// IMatrix을(를) 통해 상속됨
	void GetDesc(GE::MATRIX_DESC* pDesc) override;
	void SetDesc(GE::MATRIX_DESC* pDesc) override;
	void Multiply(GE::MATRIX_DESC* in0, GE::MATRIX_DESC* in1, GE::MATRIX_DESC* out) override;
	void CreateScaleMatrix(GE::MATRIX_DESC* out, float x, float y, float z) override;
	void CreateTranslateMatrix(GE::MATRIX_DESC* out, float x, float y, float z) override;
	void CreateRotationMatrix(GE::MATRIX_DESC* out, float x, float y, float z) override;
	void Release() override;
};