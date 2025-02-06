#pragma once
#include "Application.h"
#include "GlobalLight.h"
#include "Terrain.h"
#include "SkyBox.h"

#include "Ray.h"


#include "StaticObject.h"
#include "MapData.h"


class TestWorld : public Engine::World
{
public:
	TestWorld() = default;

	void Prepare(Engine::Content::Factory::Object* objectFactory) override;
    
protected:
	void PreInitialize(const Engine::Modules& moduels) override;
	void PreUpdate(float deltaTime) override;
	void PostUpdate(float deltaTime )override;
	void PostFixedUpdate() override;

private:
	Ray* _ray;
	GlobalLight* _light;
	Terrain* _terrain;
	SkyBox* _skyBox;

	int playerSerialNum = 0;

	Engine::Physics::IScene* mainScene;
	Engine::Physics::IScene* cameraScene;

private:
	template<typename T>
	void helpPrepare(const std::wstring& name, Engine::Content::Factory::Object* objectFactory)
	{
		auto object = GameClient::Application::GetLoadManager()->GetObjectCloneData(name);
		for (auto& data : object)
		{
			auto building = objectFactory->Clone<T>(this);
			building->SetisDynamic(data.GetProperty<bool>(L"isDynamic").value());
			building->SetIsPublic(data.GetProperty<bool>(L"isPublic").value());
			building->SetHasMesh(data.GetProperty<bool>(L"hasMesh").value());
			building->SetTransform({
					data.GetProperty<Engine::Math::Vector3>(L"position").value(),
					data.GetProperty<Engine::Math::Quaternion>(L"rotation").value(),
					data.GetProperty<Engine::Math::Vector3>(L"scale").value()
				});
			building->SetBoxScale(data.GetProperty<Engine::Math::Vector3>(L"boxScale").value());
		}
	}
};

