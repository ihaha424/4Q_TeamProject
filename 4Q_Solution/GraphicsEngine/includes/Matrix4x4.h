#pragma once
#include <directxtk/SimpleMath.h>

namespace GE
{
	struct Matrix4x4 : public DirectX::SimpleMath::Matrix 
	{
		Matrix4x4() = default;
		Matrix4x4(const DirectX::SimpleMath::Matrix& matrix) : DirectX::SimpleMath::Matrix(matrix)	{}
	};
}