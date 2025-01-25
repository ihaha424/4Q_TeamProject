#pragma once

namespace Engine::Physics
{
	// Engine Interface
	struct Geometry
	{
		Geometry() = default;
		Geometry(const Geometry& other) = default;
		Geometry(Geometry&& other) noexcept = default;
		Geometry& operator=(const Geometry& other) = default;
		Geometry& operator=(Geometry&& other) noexcept = default;
		virtual ~Geometry() = default;

		virtual void	SetScale(const Engine::Math::Vector3& position) = 0;
		virtual const	Engine::Math::Vector3 GetScale() const			= 0;

		virtual GeometryShape SetType(GeometryShape type)	= 0;
		virtual void GetType(GeometryShape type)			= 0;
	};
}

