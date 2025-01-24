#pragma once

namespace Engine::Physics
{
	struct IPhysicsRigidComponent : Component
	{

		/********************************
					 Component
		*********************************/
		virtual void SetName(const char* Name) = 0;
		virtual const char* GetName() const = 0;


		/********************************
					   Rigid
		*********************************/
		virtual void	SetTranslate(const Engine::Math::Vector3& position) = 0;
		virtual const	Engine::Math::Vector3 GetTranslate() const = 0;

		virtual void	SetRotation(const Engine::Math::Vector4& Rotation) = 0;
		virtual const	Engine::Math::Vector4 GetRotation() const = 0;

		virtual void	SetTransform(const Engine::Math::Transform& transform) = 0;
		virtual const	Engine::Math::Transform GetTransform() const = 0;

		/********************************
				Collision CallBack
		*********************************/
		// Refer. Unity Collosion
		// »ó¼Ó?>
		virtual void OnTriggerEnter() = 0;
		virtual void OnTrigger() = 0;
		virtual void OnTriggerExit() = 0;
		virtual void OnCollisionEnter() = 0;
		virtual void OnCollision() = 0;
		virtual void OnCollisionExit() = 0;

		// Refer. Unreal Collosion
		// Binding?
		virtual void OnHit() = 0;
		virtual void OnOverlapBegin() = 0;
		virtual void OnOverlapEnd() = 0;
	};

	struct PhysicsRigidComponent : IPhysicsRigidComponent
	{
		virtual void Initialize() = 0;
		virtual void Update(float deltaTime) const = 0;
		virtual void Finalize() = 0;

		/********************************
					   Rigid
		*********************************/
		virtual bool	AttachShape(IShape* shape) = 0;
		virtual bool	DetachShape(IShape* shape) = 0;
	};
}
