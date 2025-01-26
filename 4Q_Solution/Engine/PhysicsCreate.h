#pragma once

namespace Engine::Physics
{
	struct ICreate
	{
		/********************************
					Create
		*********************************/
		virtual bool CreatePhysics(bool isVisualDebuger = true) = 0;
		virtual bool CreateScene(IScene** scene, const Utils::Description::SceneDesc& sceneDescription, const char* name = nullptr) = 0;
		virtual bool CreateObject(IObject** object, const Utils::DataStructure::RigidBodyType& type) = 0;
		virtual bool CreateGeometry(IGeometry** geometry, const Utils::Description::GeometryDesc& geometryDesc, const Utils::Description::VerticesMeshDesc verticesMeshDesc = Utils::Description::VerticesMeshDesc()) = 0;
		virtual bool CreateShape(IShape** shape, const IGeometry* geometry, const IMaterial* meterial, bool isExclusive = true) = 0;
		virtual bool CreateMaterial(IMaterial** meterial, const Utils::Description::MaterialDesc& materialDesc) = 0;

		virtual bool CreateCameraScene(IScene** scene, const Utils::Description::SceneDesc& sceneDescription) = 0;
	};
}
