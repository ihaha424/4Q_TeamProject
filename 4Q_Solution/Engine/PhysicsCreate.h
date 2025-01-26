#pragma once

namespace Engine::Physics
{
	struct ICreate
	{
		/********************************
					Create
		*********************************/
		virtual void CreateScene(IScene** scene, const SceneDesc& sceneDescription, const char* name = nullptr) = 0;
		
		virtual void CreateRigidComponent(IRigidComponent** rigidComponet, const RigidComponentDesc& rigidComponetDesc) = 0;
		
		// virtual bool CreateObject(IObject** object, const RigidBodyType& type) = 0;
		// virtual bool CreateShape(IShape** shape, const IGeometry* geometry, const IMaterial* meterial, bool isExclusive = true) = 0;
		// virtual bool CreateGeometry(IGeometry** geometry, const GeometryDesc& geometryDesc, const VerticesMeshDesc verticesMeshDesc = VerticesMeshDesc()) = 0;
		// virtual bool CreateMaterial(IMaterial** meterial, const MaterialDesc& materialDesc) = 0;

		/**
		 * @brief	: Scene's Gravity is zero.
		 */
		virtual void CreateCameraScene(IScene** scene, const SceneDesc& sceneDescription) = 0;
	};
}
