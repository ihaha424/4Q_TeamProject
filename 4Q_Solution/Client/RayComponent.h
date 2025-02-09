#pragma once
class RayComponent
	: public Engine::Component::Component
{
public:
	RayComponent();
	virtual ~RayComponent();

	void Initialize(const Engine::Modules& modules) override;
	void Update(float deltaTime) override;
	const Engine::Physics::AdditionalQueryData& RayCast(const Engine::Math::Vector3& startPosition, const Engine::Math::Vector3& direction, float distance);

private:
	Engine::Physics::IScene* raycastScene;
	Engine::Physics::AdditionalQueryData queryData;

};

