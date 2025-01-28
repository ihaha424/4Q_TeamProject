#pragma once
#include "World.h"

namespace Engine::Content::Factory
{
	template <typename T>
	concept is_world = std::derived_from<T, World>;

	class Object;

	class World : public Factory<Engine::World>
	{
	public:
		World(Object* objectFactory, Engine::World** cloned);

		template<is_world T>
		T* Clone()
		{
			T* t = Factory::Copy<T>();
			t->Prepare(_objectFactory);
			*_cloned = t;
			return t;
		}

	private:
		Object* _objectFactory;
		Engine::World** _cloned;
	};
}
