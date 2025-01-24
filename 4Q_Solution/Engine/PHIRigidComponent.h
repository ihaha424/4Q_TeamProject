#pragma once


namespace Engine::PHI
{
	class PHICollisionComponent final
	{
	public:
		void __CALLBACK__ OnTriggerEnter() override;
		void __CALLBACK__ OnTrigger() override;
		void __CALLBACK__ OnTriggerExit() override;
		void __CALLBACK__ OnCollisionEnter() override;
		void __CALLBACK__ OnCollision() override;
		void __CALLBACK__ OnCollisionExit() override;

		void __CALLBACK__ OnHit() override;
		void __CALLBACK__ OnOverlapBegin() override;
		void __CALLBACK__ OnOverlapEnd() override;

	private:
		Object* owner;

		void SetOwner() override;
	};
}
