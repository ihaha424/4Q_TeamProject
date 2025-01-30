#pragma once
#include "ICollision.h"

namespace PhysicsEngineAPI
{
	class PhysXCollision
		: public ICollision
	{
		union CollisionID;
	public:
		PhysXCollision();
		virtual ~PhysXCollision();

		void OnTriggerEnter(Utils::DataStructure::TriggerEvent info) override;
		void OnTrigger(Utils::DataStructure::TriggerEvent info) override;
		void OnTriggerExit(Utils::DataStructure::TriggerEvent info) override;
		void OnCollisionEnter(Utils::DataStructure::ContactEvent info) override;
		void OnCollision(Utils::DataStructure::ContactEvent info) override;
		void OnCollisionExit(Utils::DataStructure::ContactEvent info) override;


		void OnHit(Utils::DataStructure::ContactEvent info) override;
		void OnOverlapBegin(Utils::DataStructure::TriggerEvent info) override;
		void OnOverlapEnd(Utils::DataStructure::TriggerEvent info) override;
	private:
		union CollisionID
		{
			uint64_t id;
			struct
			{
				ICollision* thisId;
				ICollision* otherId;
			};
		};
		std::map<CollisionID, bool> collisionMap;
	};
}
