#pragma once

namespace Engine::Physics
{
	struct IFactory
	{
		/********************************
					Factory
		*********************************/
		virtual void CreateDynamic(
			IRigidDynamicComponent** destObject,
			const RigidComponentDesc& rigidComponetDesc,
			const Engine::Transform& transform,
			float density,
			const Engine::Transform& shapeOffset = Engine::Transform()
		) = 0;

		virtual void CreateKinematic(
			IRigidKinematicComponent** destObject,
			const RigidComponentDesc& rigidComponetDesc,
			const Engine::Transform& transform,
			float density,
			const Engine::Transform& shapeOffset = Engine::Transform()
		) = 0;

		virtual void CreateStatic(
			IRigidStaticComponent** destObject,
			const RigidComponentDesc& rigidComponetDesc,
			const Engine::Transform& transform,
			const Engine::Transform& shapeOffset = Engine::Transform()
		) = 0;


		virtual void CloneShape(
			IRigidComponent** destShape,
			const IRigidComponent* shape,
			bool isExclusive = false
		) = 0;

		virtual void CloneStatic(
			IRigidStaticComponent** destObject,
			const Engine::Transform& transform,
			const IRigidStaticComponent* object
		) = 0;

		virtual void CloneDynamic(
			IRigidStaticComponent** destObject,
			const Engine::Transform& transform,
			const IRigidStaticComponent* object
		) = 0;

		/**
		 * @brief
				: CreatePlane
		 * @param object		: IObject(RigidBodyType::Static)
		 * @param plane			: x,y,z - plane's normal / w - plane's distance from centor
		 * @param material		: Object's Material
		 * @return				: IObject(RigidBodyType::Static)
		 */
		virtual void CreatePlane(
			IRigidComponent** object,
			const Engine::Math::Vector4& plane,
			const MaterialDesc& material
		) = 0;

		/**
		 * @param point		: plane's point
		 * @param normal	: plane's normal
		 */
		virtual void CreatePlane(
			IRigidComponent** object,
			const Engine::Math::Vector3& point,
			const Engine::Math::Vector3& normal,
			const MaterialDesc& material
		) = 0;

		//void ScaleRigidActor(PxRigidActor& actor, float scale, bool scaleMassProps = true);

		/**
		 * @brief			: Creating a static bounding box for AABB
							  Usually used for actors who will make up the camera scene
		 */
		virtual void CreateStaticBoundBoxActor(
			IRigidComponent** object,
			const Engine::Math::Vector3& boxExtents = Engine::Math::Vector3{ 1, 1, 1 }) = 0;
	};
}
