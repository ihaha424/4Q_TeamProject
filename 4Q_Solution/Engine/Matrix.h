#pragma once
#include "../includes/GraphicsEngine/Matrix4x4.h"

namespace Engine::Math
{
	class Matrix : public GE::Matrix4x4
	{
	public:
		Matrix() = default;
		Matrix(const GE::Matrix4x4& matrix) : GE::Matrix4x4(matrix) {};
		Matrix(const DirectX::SimpleMath::Matrix& matrix) : GE::Matrix4x4(matrix) {};

		Matrix& operator=(const GE::Matrix4x4& matrix)
		{
			*this = Matrix(matrix);
			return *this;
		}
	};
}
