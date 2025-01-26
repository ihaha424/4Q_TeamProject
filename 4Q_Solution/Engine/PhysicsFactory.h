#pragma once

namespace Engine::Physics
{
	struct IFactory
	{
		/********************************
					Factory
		*********************************/
		virtual bool CreateDynamic(
			IDynamicObject** destObject,
			const Utils::Math::Transform& transform,
			const IGeometry* geometry,
			IMaterial* material,
			float density,
			const Utils::Math::Transform& shapeOffset = Utils::Math::Transform()
		) = 0;

		virtual bool CreateDynamic(
			IDynamicObject** destObject,
			const Utils::Math::Transform& transform,
			IShape* shape,
			float density
		) = 0;

		virtual bool CreateKinematic(
			IKinematicObject** destObject,
			const Utils::Math::Transform& transform,
			const IGeometry* geometry,
			IMaterial* material,
			float density,
			const Utils::Math::Transform& shapeOffset = Utils::Math::Transform()
		) = 0;

		virtual bool CreateKinematic(
			IKinematicObject** destObject,
			const Utils::Math::Transform& transform,
			IShape* shape,
			float density
		) = 0;

		virtual bool CreateStatic(
			IStaticObject** destObject,
			const Utils::Math::Transform& transform,
			const IGeometry* geometry,
			IMaterial* material,
			const Utils::Math::Transform& shapeOffset = Utils::Math::Transform()
		) = 0;

		virtual bool CreateStatic(
			IStaticObject** destObject,
			const Utils::Math::Transform& transform,
			IShape* shape
		) = 0;

		virtual bool CloneShape(
			IShape** destShape,
			const IShape* shape,
			bool isExclusive = false
		) = 0;

		virtual bool CloneStatic(
			IStaticObject** destObject,
			const Utils::Math::Transform& transform,
			const IObject* object
		) = 0;

		virtual bool CloneDynamic(
			IDynamicObject** destObject,
			const Utils::Math::Transform& transform,
			const IObject* object
		) = 0;

		/**
		 * @brief
				: CreatePlane
		 * @param object		: IObject(RigidBodyType::Static)
		 * @param plane			: x,y,z - plane's normal / w - plane's distance from centor
		 * @param material		: Object's Material
		 * @return				: IObject(RigidBodyType::Static)
		 */
		virtual bool CreatePlane(
			IObject** object,
			const Utils::Math::Vector4& plane,
			IMaterial* material
		) = 0;

		/**
		 * @param point		: plane's point
		 * @param normal	: plane's normal
		 */
		virtual bool CreatePlane(
			IObject** object,
			const Utils::Math::Vector3& point,
			const Utils::Math::Vector3& normal,
			IMaterial* material
		) = 0;

		//void ScaleRigidActor(PxRigidActor& actor, float scale, bool scaleMassProps = true);

		/**
		 * @brief			: Creating a static bounding box for AABB
							  Usually used for actors who will make up the camera scene
		 */
		virtual bool CreateStaticBoundBoxActor(
			IObject** object,
			const Utils::Math::Vector3& boxExtents = Utils::Math::Vector3{ 1, 1, 1 }) = 0;
	};
}
