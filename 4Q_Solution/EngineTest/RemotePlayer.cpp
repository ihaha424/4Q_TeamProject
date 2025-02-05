#include "pch.h"
#include "RemotePlayer.h"
#include "NetworkTemp.h"


RemotePlayer::RemotePlayer(std::filesystem::path&& meshPath) :
	_meshPath(std::forward<std::filesystem::path>(meshPath)), _skeletalMesh(nullptr), _animator(nullptr)
	, _worldMatrix(Engine::Math::Matrix::Identity)
{
}

void RemotePlayer::Prepare(Engine::Content::Factory::Component* componentFactory)
{
	_skeletalMesh = componentFactory->Clone<Engine::Component::SkeletalMesh>(this);
	_animator = componentFactory->Clone<Engine::Component::Animator>(this);
	_sync = componentFactory->Clone<Engine::Component::Synchronize>(this);
	_remoteMove = componentFactory->Clone<RemoteMoveComponent>(this);
}

void RemotePlayer::DisposeComponents()
{
	_skeletalMesh->Dispose();
	_animator->Dispose();
	_sync->Dispose();
	_remoteMove->Dispose();
}

void RemotePlayer::PreInitialize(const Engine::Modules& modules)
{
	Object::PreInitialize(modules);

	//_movement.SetTarget(&_transform);
	_remoteMove->SetTarget(&_transform);
	_skeletalMesh->SetFilePath(_meshPath);
	_skeletalMesh->SetMatrix(&_worldMatrix);
	_animator->SetSkeletalMesh(_skeletalMesh);

	_sync->AddCallback((short)PacketID::DataRemote, &RemotePlayer::FirstInitialize, this);
	_sync->AddCallback((short)PacketID::MoveSync, &RemotePlayer::SyncMove, this);
	_sync->AddCallback((short)PacketID::StateChange, &RemotePlayer::StateChange, this);

	const auto inputManager = Engine::Application::GetInputManager();
	Engine::Input::IMappingContext* mappingContext = nullptr;
	inputManager->GetMappingContext(L"Default", &mappingContext);
	Engine::Input::IAction* action = nullptr;
	mappingContext->GetAction(L"Move", &action);



	action->AddListener(Engine::Input::Trigger::Event::Triggered, [this](auto value)
		{
			//_movement.SetDirection(value);
		});
	action->AddListener(Engine::Input::Trigger::Event::Started, [this](auto value)
		{
			//_animator.ChangeAnimation("Run"); 
		});
	action->AddListener(Engine::Input::Trigger::Event::Completed, [this](auto value)
		{
			//_animator.ChangeAnimation("Wait");
			//_movement.SetDirection(Engine::Math::Vector3::Zero);
		});
}

void RemotePlayer::PostInitialize(const Engine::Modules& modules)
{
	Object::PostInitialize(modules);
	//_movement.SetSpeed(100.f);
	_animator->ChangeAnimation("Wait");
	/*_animator.SetUpSplitBone(2);
	_animator.SplitBone(0, "Dummy_root");
	_animator.SplitBone(1, "Bip01-Spine1");*/
	//_animator.ChangeAnimation("Wait");

	_worldMatrix = Engine::Math::Matrix::CreateScale(3.f);
}

void RemotePlayer::PostAttach()
{
	Object::PostAttach();
	//_camera.Activate();
}

void RemotePlayer::PostUpdate(float deltaTime)
{
	_worldMatrix = Engine::Math::Matrix::CreateScale(1.f) * Engine::Math::Matrix::CreateTranslation(_transform.position.x, _transform.position.y, _transform.position.z);

	//Engine::Math::Vector3 tempPostion = _transform.position;
	//tempPostion.z -= 300.f;
	//tempPostion.y += 300.f;
	//_camera.SetPosition(tempPostion);
	//_camera.SetRotation(Engine::Math::Vector3(45.f, 0.f, 0.f));
}

void RemotePlayer::SyncMove(const MoveMsg::MoveSync* msg)
{
	float x = msg->x();
	float y = msg->y();
	float z = msg->z();
	Engine::Math::Vector3 nextLocation(x, y, z);
	_remoteMove->SetNextLocation(nextLocation);
}

void RemotePlayer::FirstInitialize(const ConnectMsg::SyncPlayer* msg)
{
	float x = msg->x();
	float y = msg->y();
	float z = msg->z();
	Engine::Math::Vector3 location(x, y, z);
	_transform.position = location;
}

void RemotePlayer::StateChange(const MoveMsg::StateChange* msg)
{
	if (msg->stateinfo() == 1) {
		_animator->ChangeAnimation("Run");
	}
	else if (msg->stateinfo() == 0) {
		_animator->ChangeAnimation("Wait");
	}
}

void RemotePlayer::SetSerialNumber(int num)
{
	_sync->SetSerialNumber(num);
}

