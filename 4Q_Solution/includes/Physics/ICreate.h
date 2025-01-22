#pragma once
#include "IElementDeclaration.h"

namespace PhysicsEngineAPI
{
	__INTERFACE__
	class ICreate
	{
	public:
		// Creat Physics System
		virtual bool CreatePhysics(bool isVisualDebuger = true) = 0;
		virtual bool CreateScene(_OUT_ IScene** scene, const Utils::Description::SceneDesc& sceneDescription, const char* name = nullptr) = 0;
		virtual bool CreateObject(_OUT_ IObject** object, const Utils::DataStructure::RigidBodyType& type) = 0;
		// TODO: 여러 매쉬를 받는 것도 하면 좋을 것 같음 굳이 1개의 메쉬로?
		virtual bool CreateGeometry(_OUT_ IGeometry** geometry, const Utils::Description::GeometryDesc& geometryDesc, const Utils::Description::VerticesMeshDesc verticesMeshDesc = Utils::Description::VerticesMeshDesc()) = 0;
		virtual bool CreateShape(_OUT_ IShape** shape, const IGeometry* geometry, const IMaterial* meterial, bool isExclusive = true) = 0;
		virtual bool CreateMaterial(_OUT_ IMaterial** meterial, const Utils::Description::MaterialDesc& materialDesc) = 0;
	
		// Camera Frustum Scene
		
		/**
		 * @brief					: Scene, where all objects are static and are made for the purpose of curling with the camera.
		 * @param scene				: Out Data
		 * @param sceneDescription	: Gravity is 0, CPUDispatcherCount is valid.
		 * @return 
		 */
		virtual bool CreateCameraScene(_OUT_ IScene** scene, const Utils::Description::SceneDesc& sceneDescription) = 0;


		// TODO: 
		// Particle Scene (GPGPU사용 예정)
		// 1. 실제 씬과 상호작용할 물리 파티클 -> 본래의 씬과 같이 사용
		// 2. 실세 씬과 상호작용이 없는 효과나 움직임만 있는 Particle (물리 효과가 없는 기본적인 움직임도 같이 만들 것)
	};
}
