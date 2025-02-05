#pragma once
#include "Object.h"

namespace Engine::Content::Factory
{
	template <typename T>
	concept is_object = std::derived_from<T, Object>;

	class Component;

	class Object : public Factory<Engine::Object>
	{
	public:
		Object(Component* objectFactory, std::vector<Engine::Object*>* cloned);

		template<is_object T>
		T* Clone(World* owner)
		{
			T* t = Factory::Copy<T>();
			t->SetOwner(owner);
			t->Prepare(_componentFactory);
			_cloned->push_back(t);
			return t;
		}

	private:
		Component* _componentFactory;
		std::vector<Engine::Object*>* _cloned;
	};
}
