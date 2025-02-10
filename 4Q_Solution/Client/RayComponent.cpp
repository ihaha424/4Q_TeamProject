#include "pch.h"
#include "RayComponent.h"

RayComponent::RayComponent()
	: raycastScene{nullptr}
{
}

RayComponent::~RayComponent()
{
}

void RayComponent::Initialize(const Engine::Modules& modules)
{
	Component::Initialize(modules);
	auto PhysicsManager = Engine::Application::GetPhysicsManager();
	raycastScene = PhysicsManager->GetScene(static_cast<unsigned int>(SceneFillter::cameraScene));

}

void RayComponent::Update(float deltaTime)
{
}

const Engine::Physics::AdditionalQueryData& RayComponent::RayCast(const Engine::Math::Vector3& startPosition, const Engine::Math::Vector3& direction, float distance)
{
	raycastScene->Raycast(queryData, startPosition, direction, distance);

	return queryData;
}
