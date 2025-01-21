#pragma once

namespace Engine::Input::Modifier
{
	struct Modifier
	{
		Modifier() = default;
		Modifier(const Modifier& other) = default;
		Modifier(Modifier&& other) noexcept = default;
		Modifier& operator=(const Modifier& other) = default;
		Modifier& operator=(Modifier&& other) noexcept = default;
		virtual ~Modifier() = default;
	};
}
