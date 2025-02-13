#pragma once
#include "Application.h"
#include "GlobalLight.h"
#include "BG_Terrain.h"
#include "SkyBox.h"

#include "Player.h"
#include "Ray.h"

//Test
#include "GrabbedObject.h"
#include "TriggerArea.h"

#include "MapData.h"

#include "PuzzleData.h"

#include "TestSprite.h"
#include "GameCoreData.h"
#include "GrabData.h"

#include "PuzzleManagerSet.h"


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
	RemoteRay* _remoteRay;
	Live* _live;
	RemoteLive* _remoteLive;
	GlobalLight* _light;
	BG_Terrain* _terrain;
	SkyBox* _skyBox;
	TestSprite* _testSprite;
	Player* _currentPlayer;

	int playerSerialNum = 0;
	bool _dataLoad = false;

	Engine::Physics::IScene* mainScene;
	Engine::Physics::IScene* cameraScene;

public:
	void EnterAccept(const ConnectMsg::AddObject* msg);
	void CreatePlayer(const ConnectMsg::AddObject* msg);
	void CreateStaticObject(const ConnectMsg::AddObject* msg);
	void RequestData(const ConnectMsg::AddObject* msg);

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
			building->SetBoxPosition({ data.GetProperty<Engine::Math::Vector3>(L"boxPosition").value() });
			building->SetBoxScale(data.GetProperty<Engine::Math::Vector3>(L"boxScale").value());
			building->SetIsSphere(data.GetProperty<bool>(L"isSphere").value());
		}
	}

	void InitializeGameStateManager(const Engine::Modules& modules);
};

