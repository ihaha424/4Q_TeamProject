#pragma once

namespace Engine::Physics
{
	struct IUpdate
	{
		/********************************
					Update
		*********************************/
		virtual void UpdateScene(unsigned int sceneNumber, const float deltaTime) = 0;
		virtual void UpdateScene(IScene* scene, const float deltaTime) = 0;
		virtual void FetchScene(unsigned int sceneNumber, bool block = true) = 0;
		virtual void FetchScene(IScene* scene, bool block = true) = 0;
		virtual bool CheckResults(unsigned int sceneNumber, bool block = true) = 0;
		virtual bool CheckResults(IScene* scene, bool block = true) = 0;
	};
}
