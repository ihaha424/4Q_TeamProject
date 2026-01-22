#pragma once

namespace Engine::DSHContent
{
	class Manager final : public Content::Manager
	{
	public:
		Manager();

		void Initialize() override;
		void Finalize() override;

		void Contraction(const Modules& modules) override;
		void Update(float deltaTime) override;
		void LazyUpdate(float deltaTime) override;
		void FixedUpdate() override;
		void Relaxation() override;

		Content::Factory::World* GetWorldFactory() override;
		Content::Factory::Object* GetObjectFactory() override;
		Content::Factory::Component* GetComponentFactory() override;

	private:
		void Dispose();

		Content::Factory::Component _componentFactory;
		Content::Factory::Object _objectFactory;
		Content::Factory::World _worldFactory;

		std::vector<Component::Component*> _clonedComponents;
		std::vector<Component::Component*> _components;
		std::vector<Object*> _clonedObjects;
		std::vector<Object*> _objects;
		World* _clonedWorld;
		World* _world;
	};
}
