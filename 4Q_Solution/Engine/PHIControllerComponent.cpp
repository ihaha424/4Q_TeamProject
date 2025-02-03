#include "pch.h"
#include "PHIControllerComponent.h"
#include "PHICoordinateConvert.h"

using namespace Engine::PHI::CONVERT;
namespace Engine::PHI
{
	Controller::Controller()
		: controller{ nullptr }
		, collision{ nullptr }
		, controllerCollisionFlag{ 0 }
		, mass{ 1 }
		, velocity{ }
		, force{ }
	{
		collision = new Collision<Controller>{ this };
	}

	void Controller::SetName(const char* Name)
	{
		controller->SetName(Name);
	}
	const char* Controller::GetName() const
	{
		return controller->GetName();
	}
	void Controller::ClearUserData()
	{
		controller->ClearUserData();
	}

	unsigned short Controller::Move(const Engine::Math::Vector3 displacement, float minDistance, float deltaTime)
	{

		return controllerCollisionFlag = controller->Move(Vector3ToPhysicsVector3(displacement), minDistance, deltaTime);
	}

	void Controller::SetGravity(const Engine::Math::Vector3& _gravity)
	{
		gravity = _gravity;
	}
	const Engine::Math::Vector3& Controller::GetGravity() const
	{
		return gravity;
	}

	void Controller::SetTotalGravity(const Engine::Math::Vector3& gravity)
	{
		totalGravity = gravity;
	}

	const Engine::Math::Vector3& Controller::GetTotalGravity() const
	{
		return totalGravity;
	}

	void Controller::SetPosition(const Engine::Math::Vector3& position)
	{
		controller->SetPosition(Vector3ToPhysicsVector3(position));
	}
	const Engine::Math::Vector3& Controller::GetPosition() const
	{
		return PhysicsVector3ToVector3(controller->GetPosition());
	}

	void Controller::SetBottomPosition(const Engine::Math::Vector3& position)
	{
		controller->SetBottomPosition(Vector3ToPhysicsVector3(position));
	}
	const Engine::Math::Vector3& Controller::GetBottomPosition() const
	{
		return PhysicsVector3ToVector3(controller->GetBottomPosition());
	}

	void Controller::SetStepOffset(float offset)
	{
		controller->SetStepOffset(offset);
	}
	float Controller::GetStepOffset() const
	{
		return controller->GetStepOffset();
	}

	void Controller::SetNonWalkSlide(const Engine::Physics::ControllerSlope mode)
	{
		controller->SetNonWalkSlide(static_cast<PhysicsEngineAPI::Utils::DataStructure::ControllerSlope>(mode));
	}
	Engine::Physics::ControllerSlope Controller::GetNonWalkSlide() const
	{
		return static_cast<Engine::Physics::ControllerSlope>(controller->GetNonWalkSlide());
	}

	void Controller::SetContactOffset(float offset)
	{
		controller->SetContactOffset(offset);
	}
	float Controller::GetContactOffset() const
	{
		return controller->GetContactOffset();
	}

	void Controller::SetUpDirection(const Engine::Math::Vector3& direction)
	{
		controller->SetUpDirection(Vector3ToPhysicsVector3(direction));
	}
	const Engine::Math::Vector3& Controller::GetUpdirection() const
	{
		return PhysicsVector3ToVector3(controller->GetUpdirection());
	}

	void Controller::SetSlopeLimit(float limit)
	{
		controller->SetSlopeLimit(limit);
	}
	float Controller::GetSlopeLimit() const
	{
		return controller->GetSlopeLimit();
	}

	void Controller::InvalidateCache()
	{
		controller->InvalidateCache();
	}

	void Controller::GetState(Engine::Physics::ControllerState& _state) const
	{
		PhysicsEngineAPI::Utils::DataStructure::ControllerState state{};
		controller->GetState(state);

		_state.position = PhysicsVector3ToVector3(state.position);
		_state.controllerCollisionFlag = state.controllerCollisionFlag;
		_state.isStandingCCT = state.isStandingCCT;
		_state.isStandingObstacle = state.isStandingObstacle;
		_state.isMovingUp = state.isMovingUp;
	}

	void Controller::SetRadius(float offset)
	{
		controller->SetRadius(offset);
	}
	float Controller::GetRadius() const
	{
		return controller->GetRadius();
	}

	void Controller::SetHeight(float offset)
	{
		controller->SetHeight(offset);
	}
	float Controller::GetHeight() const
	{
		return controller->GetHeight();
	}

	void Controller::SetClimbingMode(const Engine::Physics::CapsuleClimbingMode mode)
	{
		controller->SetClimbingMode(static_cast<PhysicsEngineAPI::Utils::DataStructure::CapsuleClimbingMode>(mode));
	}
	Engine::Physics::CapsuleClimbingMode Controller::GetClimbingMode() const
	{
		return static_cast<Engine::Physics::CapsuleClimbingMode>(controller->GetClimbingMode());
	}



	/***********************************
				Engine
	************************************/
	void Controller::Initialize()
	{
		controller->SetUserData(collision);
	}
	void Controller::Update(float deltaTime)
	{
		Engine::Math::Vector3 acceleration = force / mass;

		velocity += (acceleration * deltaTime);

		gravity += totalGravity;

		velocity += gravity;

		controllerCollisionFlag = controller->Move(Vector3ToPhysicsVector3(velocity * deltaTime), 0.001f, deltaTime);
		if (controllerCollisionFlag & 0x04 || controllerCollisionFlag & 0x01)
		{
			gravity.y = 0;
		}
		
		force = Engine::Math::Vector3::Zero;
	}
	void Controller::Finalize()
	{
		constexpr Utility::SafeRelease releaser;

		releaser(&collision);
		releaser(&controller);
	}
	unsigned short Controller::GetCollisionFlag()
	{
		return controllerCollisionFlag;
	}
	void Controller::FixedUpdate()
	{
		collision->FixedUpdate();
	}


	/***********************************
			Kinematic Move Setting
	************************************/
	void Controller::AddForce(const Engine::Math::Vector3& _force)
	{
		force += _force;
	}
	void Controller::AddVelocity(const Engine::Math::Vector3& _velocity)
	{
		velocity += _velocity;
	}
	void Controller::SetVelocity(const Engine::Math::Vector3& _velocity)
	{
		velocity = _velocity;
	}
	Engine::Math::Vector3 Controller::GetVelocity()
	{
		return Engine::Math::Vector3();
	}
	void Controller::ClearVelocity()
	{
		velocity = Engine::Math::Vector3::Zero;
	}
	void Controller::SetMass(float _mass)
	{
		mass = _mass;
	}
	float Controller::GetMass()
	{
		return mass;
	}
}