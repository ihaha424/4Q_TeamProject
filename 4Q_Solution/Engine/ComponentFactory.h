#pragma once

namespace Engine::Content::Factory
{
	template <typename T>
	concept is_component = std::derived_from<T, Component::Component>;

	class Component : public Factory<Engine::Component::Component>
	{
	public:
		explicit Component(std::vector<Engine::Component::Component*>* cloned);

		template<is_component T>
		T* Clone(Object* owner)
		{
			T* t = Factory::Copy<T>();
			t->SetOwner(owner);
			_cloned->push_back(t);
			return t;
		}

	private:
		std::vector<Engine::Component::Component*>* _cloned;
	};
}
