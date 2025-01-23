#pragma once

namespace Engine::Math
{
	struct Quaternion : DirectX::SimpleMath::Quaternion
	{
		using DirectX::SimpleMath::Quaternion::Identity;

		Quaternion(const DirectX::SimpleMath::Quaternion& quaternion) noexcept;

		Quaternion& operator=(const DirectX::SimpleMath::Quaternion& quaternion) noexcept;
	};
}