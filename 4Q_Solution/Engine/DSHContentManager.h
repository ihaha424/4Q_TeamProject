#pragma once

namespace Engine::DSHContent
{
	class Manager final : public Content::Manager
	{
	public:
		void Finalize() override;

		Content::Factory<World>& GetWorldFactory() override;

		Content::Factory<Object>& GetObjectFactory() override;

		Content::Factory<Component::Component>& GetComponentFactory() override;

	private:
		Content::Factory<World> _worldFactory;
		Content::Factory<Object> _objectFactory;
		Content::Factory<Component::Component> _componentFactory;
	};
}
