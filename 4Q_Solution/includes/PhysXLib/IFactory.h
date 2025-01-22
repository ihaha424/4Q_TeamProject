#pragma once
#include "IElementDeclaration.h"

namespace Physics
{
	__INTERFACE__
		class IFactory
	{
	public:
		virtual bool CreateDynamic(
			_OUT_ IDynamicObject** destObject,
			const Physics::Utils::Math::Transform& transform,
			const IGeometry* geometry,
			IMaterial* material,
			float density,
			const Physics::Utils::Math::Transform& shapeOffset = Physics::Utils::Math::Transform()
		) = 0;

		virtual bool CreateDynamic(
			_OUT_ IDynamicObject** destObject,
			const Physics::Utils::Math::Transform& transform,
			IShape* shape,
			float density
		) = 0;

		virtual bool CreateKinematic(
			_OUT_ IKinematicObject** destObject,
			const Physics::Utils::Math::Transform& transform,
			const IGeometry* geometry,
			IMaterial* material,
			float density,
			const Physics::Utils::Math::Transform& shapeOffset = Physics::Utils::Math::Transform()
		) = 0;

		virtual bool CreateKinematic(
			_OUT_ IKinematicObject** destObject,
			const Physics::Utils::Math::Transform& transform,
			IShape* shape,
			float density
		) = 0;

		virtual bool CreateStatic(
			_OUT_ IStaticObject** destObject,
			const Physics::Utils::Math::Transform& transform,
			const IGeometry* geometry,
			IMaterial* material,
			const Physics::Utils::Math::Transform& shapeOffset = Physics::Utils::Math::Transform()
		) = 0;

		virtual bool CreateStatic(
			_OUT_ IStaticObject** destObject,
			const Physics::Utils::Math::Transform& transform,
			IShape* shape
		) = 0;

		virtual bool CloneShape(
			_OUT_ IShape** destShape,
			const IShape* shape,
			bool isExclusive = false
		) = 0;

		virtual bool CloneStatic(
			_OUT_ IStaticObject** destObject,
			const Physics::Utils::Math::Transform& transform,
			const IObject* object
		) = 0;

		virtual bool CloneDynamic(
			_OUT_ IDynamicObject** destObject,
			const Physics::Utils::Math::Transform& transform,
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
			_OUT_ IObject** object,
			const Utils::Math::Vector4& plane,
			IMaterial* material
		) = 0;

		/**
		 * @param point		: plane's point
		 * @param normal	: plane's normal
		 */
		virtual bool CreatePlane(
			_OUT_ IObject** object,
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
			_OUT_ IObject** object,
			const Utils::Math::Vector3& boxExtents = Utils::Math::Vector3{1, 1, 1}) = 0;

	};

}

