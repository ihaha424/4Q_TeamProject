#pragma once

namespace Engine::PHI
{
	template<typename T>
	class Collision
		: public Physics::Collision
		, public PhysicsEngineAPI::ICollision
	{
	public:
		Collision(T* rigidComponent);
        virtual ~Collision();

		// PhysicsEngineAPI
		void __CALLBACK__ OnTriggerEnter(PhysicsEngineAPI::Utils::DataStructure::TriggerEvent info) override;
		void __CALLBACK__ OnTrigger(PhysicsEngineAPI::Utils::DataStructure::TriggerEvent info) override;
		void __CALLBACK__ OnTriggerExit(PhysicsEngineAPI::Utils::DataStructure::TriggerEvent info) override;
		void __CALLBACK__ OnCollisionEnter(PhysicsEngineAPI::Utils::DataStructure::ContactEvent info) override;
		void __CALLBACK__ OnCollision(PhysicsEngineAPI::Utils::DataStructure::ContactEvent info) override;
		void __CALLBACK__ OnCollisionExit(PhysicsEngineAPI::Utils::DataStructure::ContactEvent info) override;
		void __CALLBACK__ OnHit(PhysicsEngineAPI::Utils::DataStructure::ContactEvent info) override;
		void __CALLBACK__ OnOverlapBegin(PhysicsEngineAPI::Utils::DataStructure::TriggerEvent info) override;
		void __CALLBACK__ OnOverlapEnd(PhysicsEngineAPI::Utils::DataStructure::TriggerEvent info) override;
	
	public:
		void BindCollision(const Physics::CallBackTrigger& callback, Physics::TriggerType type) override;
		void BindCollision(const Physics::CallBackContact& callback, Physics::ContactType type) override;

		void FixedUpdate() override;
        void Release() override;

        T* rigidComponent;
	private:
		void ConvertTriggerEvent(PhysicsEngineAPI::Utils::DataStructure::TriggerEvent& API, Engine::Physics::TriggerEvent& engine);
		void ConvertContactEvent(PhysicsEngineAPI::Utils::DataStructure::ContactEvent& API, Engine::Physics::ContactEvent& engine);

		struct CallBackTriggerFunctions
		{
			bool isOn{ false };
			int eventIndex{ 0 };
			std::vector<Physics::TriggerEvent> event;
			std::vector<Physics::CallBackTrigger> function;
		};

		struct CallBackContactFunctions
		{
			bool isOn{ false };
			int eventIndex{ 0 };
			std::vector<Physics::ContactEvent> event;
			std::vector<Physics::CallBackContact> function;
		};


		bool dirtyFlag;
		std::vector<CallBackTriggerFunctions> triggerFunctions;
		std::vector<CallBackContactFunctions> contactFunctions;
	};
}






namespace Engine::PHI
{
    template<typename T>
    inline Collision<T>::Collision(T* _rigidComponent)
        : rigidComponent{ _rigidComponent }
        , triggerFunctions{}
        , contactFunctions{}
        , dirtyFlag{ false }
    {
        triggerFunctions.resize(static_cast<int>(Engine::Physics::TriggerType::End));
        contactFunctions.resize(static_cast<int>(Engine::Physics::ContactType::End));
    }

    template<typename T>
    inline Collision<T>::~Collision()
    {
        
    }


    template<typename T>
    inline void Collision<T>::BindCollision(const Physics::CallBackTrigger& callback, Physics::TriggerType type)
    {
        triggerFunctions[static_cast<int>(type)].function.push_back(callback);
    }

    template<typename T>
    inline void Collision<T>::BindCollision(const Physics::CallBackContact& callback, Physics::ContactType type)
    {
        contactFunctions[static_cast<int>(type)].function.push_back(callback);
    }

    template<typename T>
    inline void Collision<T>::FixedUpdate()
    {
        if (!dirtyFlag)
            return;
        for (auto& triggerFunction : triggerFunctions)
        {
            if (!triggerFunction.isOn)
                continue;
            for (auto& trigger : triggerFunction.function)
            {
                for (int i = 0; i < triggerFunction.eventIndex; i++)
                    trigger(triggerFunction.event[i]);
            }

            triggerFunction.isOn = false;
            triggerFunction.eventIndex = 0;
        }
        for (auto& contactFunction : contactFunctions)
        {
            if (!contactFunction.isOn)
                continue;
            for (auto& trigger : contactFunction.function)
            {
                for (int i = 0; i < contactFunction.eventIndex; i++)
                    trigger(contactFunction.event[i]);
            }

            contactFunction.isOn = false;
            contactFunction.eventIndex = 0;
        }
        dirtyFlag = false;
    }

    template<typename T>
    inline void Collision<T>::Release()
    {
    }

    template<typename T>
    inline void Collision<T>::ConvertTriggerEvent(PhysicsEngineAPI::Utils::DataStructure::TriggerEvent& API, Engine::Physics::TriggerEvent& engine)
    {
        engine.myCollision = static_cast<Collision*>(API.myCollision)->rigidComponent;
        engine.otherCollision = static_cast<Collision*>(API.otherCollision)->rigidComponent;
    }

    template<typename T>
    inline void Collision<T>::ConvertContactEvent(PhysicsEngineAPI::Utils::DataStructure::ContactEvent& API, Engine::Physics::ContactEvent& engine)
    {
        ConvertTriggerEvent(API, engine);
        engine.impulse = API.impulse;
    }






    /********************************
               PhysicsEngineAPI
    *********************************/
    template<typename T>
    inline void __CALLBACK__ Collision<T>::OnTriggerEnter(PhysicsEngineAPI::Utils::DataStructure::TriggerEvent info)
    {
        dirtyFlag = true;

        auto& callBack = triggerFunctions[static_cast<int>(Physics::TriggerType::OnTriggerEnter)];
        callBack.isOn = true;
        if (callBack.eventIndex <= callBack.event.size())
            callBack.event.push_back(Physics::TriggerEvent{});
        ConvertTriggerEvent(info, callBack.event[callBack.eventIndex++]);
    }
    template<typename T>
    inline void __CALLBACK__ Collision<T>::OnTrigger(PhysicsEngineAPI::Utils::DataStructure::TriggerEvent info)
    {
        dirtyFlag = true;

        auto& callBack = triggerFunctions[static_cast<int>(Physics::TriggerType::OnTrigger)];
        callBack.isOn = true;
        if (callBack.eventIndex <= callBack.event.size())
            callBack.event.push_back(Physics::TriggerEvent{});
        ConvertTriggerEvent(info, callBack.event[callBack.eventIndex++]);
    }
    template<typename T>
    inline void __CALLBACK__ Collision<T>::OnTriggerExit(PhysicsEngineAPI::Utils::DataStructure::TriggerEvent info)
    {
        dirtyFlag = true;

        auto& callBack = triggerFunctions[static_cast<int>(Physics::TriggerType::OnTriggerExit)];
        callBack.isOn = true;
        if (callBack.eventIndex <= callBack.event.size())
            callBack.event.push_back(Physics::TriggerEvent{});
        ConvertTriggerEvent(info, callBack.event[callBack.eventIndex++]);
    }
    template<typename T>
    inline void __CALLBACK__ Collision<T>::OnCollisionEnter(PhysicsEngineAPI::Utils::DataStructure::ContactEvent info)
    {
        dirtyFlag = true;

        auto& callBack = contactFunctions[static_cast<int>(Physics::ContactType::OnCollisionEnter)];
        callBack.isOn = true;
        if (callBack.eventIndex <= callBack.event.size())
            callBack.event.push_back(Physics::ContactEvent{});
        ConvertContactEvent(info, callBack.event[callBack.eventIndex++]);
    }
    template<typename T>
    inline void __CALLBACK__ Collision<T>::OnCollision(PhysicsEngineAPI::Utils::DataStructure::ContactEvent info)
    {
        dirtyFlag = true;

        auto& callBack = contactFunctions[static_cast<int>(Physics::ContactType::OnCollision)];
        callBack.isOn = true;
        if (callBack.eventIndex <= callBack.event.size())
            callBack.event.push_back(Physics::ContactEvent{});
        ConvertContactEvent(info, callBack.event[callBack.eventIndex++]);
    }
    template<typename T>
    inline void __CALLBACK__ Collision<T>::OnCollisionExit(PhysicsEngineAPI::Utils::DataStructure::ContactEvent info)
    {
        dirtyFlag = true;

        auto& callBack = contactFunctions[static_cast<int>(Physics::ContactType::OnCollisionExit)];
        callBack.isOn = true;
        if (callBack.eventIndex <= callBack.event.size())
            callBack.event.push_back(Physics::ContactEvent{});
        ConvertContactEvent(info, callBack.event[callBack.eventIndex++]);
    }
    template<typename T>
    inline void __CALLBACK__ Collision<T>::OnHit(PhysicsEngineAPI::Utils::DataStructure::ContactEvent info)
    {
        dirtyFlag = true;

        auto& callBack = contactFunctions[static_cast<int>(Physics::ContactType::OnHit)];
        callBack.isOn = true;
        if (callBack.eventIndex <= callBack.event.size())
            callBack.event.push_back(Physics::ContactEvent{});
        ConvertContactEvent(info, callBack.event[callBack.eventIndex++]);
    }
    template<typename T>
    inline void __CALLBACK__ Collision<T>::OnOverlapBegin(PhysicsEngineAPI::Utils::DataStructure::TriggerEvent info)
    {
        dirtyFlag = true;

        auto& callBack = triggerFunctions[static_cast<int>(Physics::TriggerType::OnOverlapBegin)];
        callBack.isOn = true;
        if (callBack.eventIndex <= callBack.event.size())
            callBack.event.push_back(Physics::TriggerEvent{});
        ConvertTriggerEvent(info, callBack.event[callBack.eventIndex++]);
    }
    template<typename T>
    inline void __CALLBACK__ Collision<T>::OnOverlapEnd(PhysicsEngineAPI::Utils::DataStructure::TriggerEvent info)
    {
        dirtyFlag = true;

        auto& callBack = triggerFunctions[static_cast<int>(Physics::TriggerType::OnOverlapEnd)];
        callBack.isOn = true;
        if (callBack.eventIndex <= callBack.event.size())
            callBack.event.push_back(Physics::TriggerEvent{});
        ConvertTriggerEvent(info, callBack.event[callBack.eventIndex++]);
    }
}

