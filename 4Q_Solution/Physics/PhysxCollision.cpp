#include "pch.h"
#include "PhysXCollision.h"


namespace PhysicsEngineAPI
{
	PhysXCollision::PhysXCollision()
		: collisionMap{}
	{
	}

	PhysXCollision::~PhysXCollision()
	{
		collisionMap.clear();
	}
	void PhysXCollision::OnTriggerEnter(Utils::DataStructure::TriggerEvent info)
	{
	}
	void PhysXCollision::OnTrigger(Utils::DataStructure::TriggerEvent info)
	{
	}
	void PhysXCollision::OnTriggerExit(Utils::DataStructure::TriggerEvent info)
	{
	}
	void PhysXCollision::OnCollisionEnter(Utils::DataStructure::ContactEvent info)
	{
	}
	void PhysXCollision::OnCollision(Utils::DataStructure::ContactEvent info)
	{
	}
	void PhysXCollision::OnCollisionExit(Utils::DataStructure::ContactEvent info)
	{
	}
	void PhysXCollision::OnHit(Utils::DataStructure::ContactEvent info)
	{
	}
	void PhysXCollision::OnOverlapBegin(Utils::DataStructure::TriggerEvent info)
	{
	}
	void PhysXCollision::OnOverlapEnd(Utils::DataStructure::TriggerEvent info)
	{
	}
}
