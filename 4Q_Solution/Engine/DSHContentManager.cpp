#include "pch.h"
#include "DSHContentManager.h"

Engine::DSHContent::Manager::Manager() :
	_componentFactory(&_clonedComponents),
	_objectFactory(&_componentFactory, &_clonedObjects),
	_worldFactory(&_objectFactory, &_clonedWorld),
	_clonedWorld(nullptr),
	_world(nullptr)
{
}

void Engine::DSHContent::Manager::Initialize()
{
}

void Engine::DSHContent::Manager::Finalize()
{
	Dispose();
}

void Engine::DSHContent::Manager::Contraction(const Modules& modules)
{
	if (_clonedWorld != nullptr)_clonedWorld->PreInitialize(modules);
	std::ranges::for_each(_clonedObjects, [modules](Object* object) { object->PreInitialize(modules); });
	std::ranges::for_each(_clonedComponents, [modules](Component::Component* component) { component->Initialize(modules); });
	std::ranges::for_each(_clonedObjects, [modules](Object* object) { object->PostInitialize(modules); });
	if (_clonedWorld != nullptr)_clonedWorld->PostInitialize(modules);

	if (_clonedWorld != nullptr)_clonedWorld->PreAttach();
	std::ranges::for_each(_clonedObjects, [](Object* object) { object->PreAttach(); });
	std::ranges::for_each(_clonedComponents, [](Component::Component* component) { component->Attach(); });
	std::ranges::for_each(_clonedObjects, [](Object* object) { object->PostAttach(); });
	if (_clonedWorld != nullptr)_clonedWorld->PostAttach();

	if (_clonedWorld != nullptr)
	{
		assert(_world == nullptr);
		_world = _clonedWorld;
		_clonedWorld = nullptr;
	}

	if (_clonedObjects.empty() == false)
	{
		_objects.insert(_objects.end(), std::make_move_iterator(_clonedObjects.begin()), std::make_move_iterator(_clonedObjects.end()));
		_clonedObjects.clear();
	}

	if (_clonedComponents.empty() == false)
	{
		_components.insert(_components.end(), std::make_move_iterator(_clonedComponents.begin()), std::make_move_iterator(_clonedComponents.end()));
		_clonedComponents.clear();
	}
}

void Engine::DSHContent::Manager::Update(float deltaTime)
{
	_world->PreUpdate(deltaTime);
	std::ranges::for_each(_objects, [deltaTime](Object* object) { object->PreUpdate(deltaTime); });
	std::ranges::for_each(_components, [deltaTime](Component::Component* component) { component->Update(deltaTime); });
	std::ranges::for_each(_objects, [deltaTime](Object* object) { object->PostUpdate(deltaTime); });
	_world->PostUpdate(deltaTime);
}

void Engine::DSHContent::Manager::FixedUpdate()
{
	_world->PreFixedUpdate();
	std::ranges::for_each(_objects, [](Object* object) { object->PreFixedUpdate(); });
	std::ranges::for_each(_components, [](Component::Component* component) { component->FixedUpdate(); });
	std::ranges::for_each(_objects, [](Object* object) { object->PostFixedUpdate(); });
	_world->PostFixedUpdate();
}

void Engine::DSHContent::Manager::Relaxation()
{
	if (_clonedWorld != nullptr)
	{
		Dispose();
	}
	else
	{
		auto disposedObjects = _objects | std::views::filter([](const Object* object) {return object->IsDisposed(); });
		auto disposedComponents = _components | std::views::filter([](const Component::Component* component) {return component->IsDisposed(); });

		std::ranges::for_each(disposedObjects, [](Object* object) {object->PreDetach(); });
		std::ranges::for_each(disposedComponents, [](Component::Component* component) {component->Detach(); });
		std::ranges::for_each(disposedObjects, [](Object* object) {object->PostDetach(); });

		std::ranges::for_each(disposedObjects, [](Object* object) {object->PreFinalize(); });
		std::ranges::for_each(disposedComponents, [](Component::Component* component) {component->Finalize(); });
		std::ranges::for_each(disposedObjects, [](Object* object) {object->PostFinalize(); });

		std::ranges::for_each(disposedComponents, Utility::SafeDelete());
		std::ranges::for_each(disposedObjects, Utility::SafeDelete());

		std::erase_if(_objects, [](const Object* object) { return object == nullptr; });
		std::erase_if(_components, [](const Component::Component* component) { return component == nullptr; });
	}
}

Engine::Content::Factory::World* Engine::DSHContent::Manager::GetWorldFactory()
{
	return &_worldFactory;
}

Engine::Content::Factory::Object* Engine::DSHContent::Manager::GetObjectFactory()
{
	return &_objectFactory;
}

Engine::Content::Factory::Component* Engine::DSHContent::Manager::GetComponentFactory()
{
	return &_componentFactory;
}

void Engine::DSHContent::Manager::Dispose()
{
	_world->PreDetach();
	std::ranges::for_each(_objects, [](Object* object) { object->PreDetach(); });
	std::ranges::for_each(_components, [](Component::Component* component) { component->Detach(); });
	std::ranges::for_each(_objects, [](Object* object) { object->PostDetach(); });
	_world->PostDetach();

	_world->PreFinalize();
	std::ranges::for_each(_objects, [](Object* object) { object->PreFinalize(); });
	std::ranges::for_each(_components, [](Component::Component* component) { component->Finalize(); });
	std::ranges::for_each(_objects, [](Object* object) { object->PostFinalize(); });
	_world->PostFinalize();

	std::ranges::for_each(_components, Utility::SafeDelete());
	std::ranges::for_each(_objects, Utility::SafeDelete());
	Utility::SafeDelete()(&_world);

	_components.clear();
	_objects.clear();
	_world = nullptr;
}
