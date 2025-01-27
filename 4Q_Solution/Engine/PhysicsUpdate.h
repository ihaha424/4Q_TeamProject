#pragma once

namespace Engine::Physics
{
	struct IUpdate
	{
		/********************************
					Update
		*********************************/
		virtual void UpdateSecne(unsigned int sceneNumber, const float deltaTime) = 0;
		virtual void UpdateSecne(IScene* scene, const float deltaTime) = 0;
		virtual void FetchSecne(unsigned int sceneNumber, bool block = true) = 0;
		virtual void FetchSecne(IScene* scene, bool block = true) = 0;
		virtual bool CheckResults(unsigned int sceneNumber, bool block = true) = 0;
		virtual bool CheckResults(IScene* scene, bool block = true) = 0;
	};
}
