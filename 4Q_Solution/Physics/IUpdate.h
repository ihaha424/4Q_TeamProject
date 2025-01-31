#pragma once
#include "IElementDeclaration.h"

namespace PhysicsEngineAPI
{
	__INTERFACE__
	EXTERN_C class PHYSICS_API IUpdate
	{
	public:
		virtual ~IUpdate() = default;


		// Frame Per Physics System
		virtual void UpdateScene(unsigned int sceneNumber, const float deltaTime) = 0;
		virtual void UpdateScene(IScene* scene, const float deltaTime) = 0;
		virtual void FetchScene(unsigned int sceneNumber, bool block = true) = 0;
		virtual void FetchScene(IScene* scene, bool block = true) = 0;
		virtual bool CheckResults(unsigned int sceneNumber, bool block = true) = 0;
		virtual bool CheckResults(IScene* scene, bool block = true) = 0;


		// TODO:
		// This method must be called after collide() and before advance().
		// fetchCollision
	};
}
