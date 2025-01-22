#pragma once
#include "IElementDeclaration.h"

namespace Physics
{
	__INTERFACE__
	class IUpdate
	{
	public:
		// Frame Per Physics System
		virtual void UpdateSecne(unsigned int sceneNumber, const float deltaTime) = 0;
		virtual void UpdateSecne(IScene* scene, const float deltaTime) = 0;
		virtual void FetchSecne(unsigned int sceneNumber, bool block = true) = 0;
		virtual void FetchSecne(IScene* scene, bool block = true) = 0;
		virtual bool CheckResults(unsigned int sceneNumber, bool block = true) = 0;
		virtual bool CheckResults(IScene* scene, bool block = true) = 0;


		// TODO:
		// This method must be called after collide() and before advance().
		// fetchCollision
	};
}
