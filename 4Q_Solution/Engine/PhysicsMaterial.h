#pragma once

namespace Engine::Physics
{
	// Engine Interface
	struct Material
	{
		Material() = default;
		Material(const Material& other) = default;
		Material(Material&& other) noexcept = default;
		Material& operator=(const Material& other) = default;
		Material& operator=(Material&& other) noexcept = default;
		virtual ~Material() = default;
	};
}
