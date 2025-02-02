#include "pch.h"
#include "Player.h"
#include "NetworkTemp.h"

Player::Player(std::filesystem::path&& meshPath, std::filesystem::path&& fontPath) :
	_meshPath(std::forward<std::filesystem::path>(meshPath)),
	_fontPath(std::forward<std::filesystem::path>(fontPath)), _movement(nullptr),
	_camera(nullptr)
	//_staticMesh(nullptr), 
	//_textRenderer(nullptr),
	//_skeltalMesh(L"../Resources/Player/Player.X", &_worldMatrix),
	//_animator(&_skeltalMesh)
{
}

void Player::Prepare(Engine::Content::Factory::Component* componentFactory)
{
	_movement = componentFactory->Clone<Engine::Component::Movement>();
	_camera = componentFactory->Clone<Engine::Component::Camera>();
	//_staticMesh = componentFactory->Clone<Engine::Component::StaticMesh>();
	_skeltalMesh = componentFactory->Clone<Engine::Component::SkeletalMesh>();
	_animator = componentFactory->Clone<Engine::Component::Animator>();
	_textRenderer = componentFactory->Clone<Engine::Component::TextRenderer>();
    _sync = componentFactory->Clone<Engine::Component::Synchronize>();
	_remote = componentFactory->Clone<RemoteMoveComponent>();
	_chractorController = componentFactory->Clone<Engine::Component::ChractorController>();
}

void Player::DisposeComponents()
{
    _textRenderer->Dispose();
    //_staticMesh->Dispose();
	_skeltalMesh->Dispose();
	_animator->Dispose();
    _camera->Dispose();
    _movement->Dispose();
	_sync->Dispose();
	_remote->Dispose();
	_chractorController->Dispose();
}

void Player::PreInitialize(const Engine::Modules& modules)
{
	Object::PreInitialize(modules);
	_movement->SetTarget(&_transform);
	_remote->SetTarget(&_transform);

    _camera->SetName(L"MainCamera");
    _movement->SetTarget(&_transform);
    //_staticMesh->SetFilePath(_meshPath);
    //_staticMesh->SetMatrix(&_worldMatrix);
	_skeltalMesh->SetFilePath(_meshPath);
	_skeltalMesh->SetMatrix(&_worldMatrix);
	_animator->SetSkeletalMesh(_skeltalMesh);
    _textRenderer->SetFontPath(_fontPath);

	_sync->AddCallback((short)PacketID::EnterAccept, &Player::EnterSuccess, this);
	_sync->AddCallback((short)PacketID::MoveSync, &Player::SyncMove, this);
	_sync->AddCallback((short)PacketID::DataRemote, &Player::SetLocation, this);

	//_sync.SetSerialNumber(1);

	const auto inputManager = Engine::Application::GetInputManager();
	Engine::Input::IMappingContext* mappingContext = nullptr;
	inputManager->GetMappingContext(L"Default", &mappingContext);

	Engine::Input::IAction* moveAction = nullptr;
	mappingContext->GetAction(L"Move", &moveAction);
	moveAction->AddListener(Engine::Input::Trigger::Event::Triggered, [this](auto value)
	{
		Engine::Math::Vector3 direction = _movement->GetDirection();
		if (direction != Engine::Math::Vector3(value)) {
			//_movement.SetDirection(value);		
			
			
			_sync->_move.set_x(value.x);
			_sync->_move.set_y(value.y);
			_sync->_move.set_z(value.z);
			_sync->_move.set_speed(_movement->GetSpeed());

			_sync->_move.SerializeToString(&_sync->_msgBuffer);

			Engine::Application::GetNetworkManager()->SaveSendData(
				(short)PacketID::Move,
				_sync->_msgBuffer,
				_sync->_move.ByteSizeLong(),
				_sync->GetSerialNumber()
			);


			//NetworkTemp::GetInstance()->_move.set_serialnumber(1);
			//NetworkTemp::GetInstance()->_move.set_x(value.x);
			//NetworkTemp::GetInstance()->_move.set_y(value.y);
			//NetworkTemp::GetInstance()->_move.set_z(value.z);
			//NetworkTemp::GetInstance()->_move.set_speed(_movement.GetSpeed());

			//Client::SavePacketData(
			//	NetworkTemp::GetInstance()->_move.SerializeAsString(),
			//	(short)PacketID::Move,
			//	NetworkTemp::GetInstance()->_move.ByteSizeLong());
		}
		
	});
	moveAction->AddListener(Engine::Input::Trigger::Event::Started, [this](auto value) {
		_animator->ChangeAnimation("Run"); 

		_sync->_stateChange.set_stateinfo(1);
		_sync->_stateChange.SerializeToString(&_sync->_msgBuffer);

		Engine::Application::GetNetworkManager()->SaveSendData(
			(short)PacketID::StateChange,
			_sync->_msgBuffer,
			_sync->_stateChange.ByteSizeLong(),
			_sync->GetSerialNumber()
		);

		//NetworkTemp::GetInstance()->_stateChange.set_serialnumber(1);
		//NetworkTemp::GetInstance()->_stateChange.set_stateinfo(1);

		//Client::SavePacketData(
		//	NetworkTemp::GetInstance()->_stateChange.SerializeAsString(),
		//	(short)PacketID::StateChange,
		//	NetworkTemp::GetInstance()->_stateChange.ByteSizeLong());
		});
	moveAction->AddListener(Engine::Input::Trigger::Event::Completed, [this](auto value)
		{ 
			_animator->ChangeAnimation("Wait"); 
			_movement->SetDirection(Engine::Math::Vector3::Zero);

			_sync->_move.set_x(0);
			_sync->_move.set_y(0);
			_sync->_move.set_z(0);
			_sync->_move.set_speed(0);

			_sync->_move.SerializeToString(&_sync->_msgBuffer);

			Engine::Application::GetNetworkManager()->SaveSendData(
				(short)PacketID::Move,
				_sync->_msgBuffer,
				_sync->_move.ByteSizeLong(),
				_sync->GetSerialNumber()
			);

			_sync->_move.SerializeToString(&_sync->_msgBuffer);

			_sync->_stateChange.set_stateinfo(0);
			_sync->_stateChange.SerializeToString(&_sync->_msgBuffer);

			Engine::Application::GetNetworkManager()->SaveSendData(
				(short)PacketID::StateChange,
				_sync->_msgBuffer,
				_sync->_stateChange.ByteSizeLong(),
				_sync->GetSerialNumber()
			);

			//NetworkTemp::GetInstance()->_stateChange.set_serialnumber(1);
			//NetworkTemp::GetInstance()->_stateChange.set_stateinfo(0);

			//Client::SavePacketData(
			//	NetworkTemp::GetInstance()->_stateChange.SerializeAsString(),
			//	(short)PacketID::StateChange,
			//	NetworkTemp::GetInstance()->_stateChange.ByteSizeLong());
			_movement->SetDirection(Engine::Math::Vector3::Zero);
		});
	//moveAction->AddListener(Engine::Input::Trigger::Event::Started, [this](auto value) { /*_animator.ChangeAnimation("Run");*/ });
	//moveAction->AddListener(Engine::Input::Trigger::Event::Completed, [this](auto value)
	//{ 
	//	//_animator.ChangeAnimation("Wait"); 

	//});

	Engine::Input::IAction* cameraAction = nullptr;
	mappingContext->GetAction(L"Camera", &cameraAction);
	cameraAction->AddListener(Engine::Input::Trigger::Event::Triggered, [this](auto value)
	{
		_camera->Rotate(value);
	});

	Engine::Physics::ControllerDesc desc;
	desc.gravity = { 0.f,-9.8f, 0.f };
	desc.height = 100.f;
	desc.radius = 20.f;
	auto PhysicsManager = Engine::Application::GetPhysicsManager();
	PhysicsManager->CreatePlayerController(&_chractorController->_controller, PhysicsManager->GetScene(0), desc);
}

void Player::PostInitialize(const Engine::Modules& modules)
{
	Object::PostInitialize(modules);
	_movement->SetSpeed(100.f);	
	_textRenderer->SetPosition(100, 100.f);
	_textRenderer->SetText(L"Hello World!");
	_textRenderer->SetFontColor(1.f, 0.f, 0.f, 1.f);
	_animator->ChangeAnimation("Wait");
	//_skeltalMesh.SetRenderLayer(0);
	/*_animator.SetUpSplitBone(2);
	_animator.SplitBone(0, "Dummy_root");
	_animator.SplitBone(1, "Bip01-Spine1");
	_animator.ChangeAnimation("Wait");*/
}

void Player::PostAttach()
{
	Object::PostAttach();
	_camera->Activate();	
}

void Player::PostUpdate(const float deltaTime)
{
	Object::PostUpdate(deltaTime);
	_worldMatrix = Engine::Math::Matrix::CreateScale(1.f) * Engine::Math::Matrix::CreateTranslation(_transform.position.x, _transform.position.y, _transform.position.z);

	Engine::Math::Vector3 tempPostion = _transform.position;
	tempPostion.z -= 300.f;
	tempPostion.y += 300.f;
	_camera->SetPosition(tempPostion);
	_camera->SetRotation(Engine::Math::Vector3(45.f, 0.f, 0.f));

	_chractorController->_controller->Move({0,0,0}, 0.1, deltaTime);
}

void Player::PostFixedUpdate()
{

}

void Player::EnterSuccess(const ConnectMsg::EnterAccept* msg)
{
	_sync->SetSerialNumber(msg->grantnumber());
}

void Player::SyncMove(const MoveMsg::MoveSync* msg)
{
	Engine::Math::Vector3 nextLocation(msg->x(), msg->y(), msg->z());
	_remote->SetNextLocation(nextLocation);
}

void Player::SetLocation(const MoveMsg::MoveSync* msg)
{
	_transform.position = Engine::Math::Vector3(msg->x(), msg->y(), msg->z());
}
