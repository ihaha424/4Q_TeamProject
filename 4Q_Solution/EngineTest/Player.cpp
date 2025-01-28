#include "pch.h"
#include "Player.h"
#include "NetworkTemp.h"

Player::Player(std::filesystem::path&& meshPath, std::filesystem::path&& fontPath) :
	_meshPath(std::forward<std::filesystem::path>(meshPath)),
	_fontPath(std::forward<std::filesystem::path>(fontPath)), _movement(nullptr),
	_camera(nullptr), _staticMesh(nullptr), _textRenderer(nullptr)
	//, _skeltalMesh(L"../Resources/Player/Player.X", &_worldMatrix)
	//, _animator(&_skeltalMesh)
{
}

void Player::Prepare(Engine::Content::Factory::Component* componentFactory)
{
	_movement = componentFactory->Clone<Engine::Component::MovementComponent>();
	_camera = componentFactory->Clone<Engine::Component::CameraComponent>();
	_staticMesh = componentFactory->Clone<Engine::Component::StaticMesh>();
	_textRenderer = componentFactory->Clone<Engine::Component::TextRenderer>();
    _sync = componentFactory->Clone<Engine::Component::SynchronizeComponent>();
}

void Player::DisposeComponents()
{
    _textRenderer->Dispose();
    _staticMesh->Dispose();
    _camera->Dispose();
    _movement->Dispose();
}

void Player::PreInitialize(const Engine::Modules& modules)
{
	Object::PreInitialize(modules);

    _camera->SetName(L"MainCamera");
    _movement->SetTarget(&_transform);
    _staticMesh->SetFilePath(_meshPath);
    _staticMesh->SetMatrix(&_worldMatrix);
    _textRenderer->SetFontPath(_fontPath);

    _sync->SetSerialNumber(1);
    
	const auto inputManager = Engine::Application::GetInputManager();
	Engine::Input::IMappingContext* mappingContext = nullptr;
	inputManager->GetMappingContext(L"Default", &mappingContext);

	Engine::Input::IAction* moveAction = nullptr;
	mappingContext->GetAction(L"Move", &moveAction);
	moveAction->AddListener(Engine::Input::Trigger::Event::Triggered, [this](auto value)
	{
		Engine::Math::Vector3 direction = _movement->GetDirection();
		if (direction != Engine::Math::Vector3(value)) {
			_movement->SetDirection(value);		
			
			
			_sync->_move.set_serialnumber(1);
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
		//_animator.ChangeAnimation("Run"); 

		_sync->_stateChange.set_serialnumber(1);
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
			//_animator.ChangeAnimation("Wait"); 
			_movement->SetDirection(Engine::Math::Vector3::Zero);

			_sync->_stateChange.set_serialnumber(1);
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
}

void Player::PostInitialize(const Engine::Modules& modules)
{
	Object::PostInitialize(modules);
	_movement->SetSpeed(100.f);	
	_textRenderer->SetPosition(100, 100.f);
	_textRenderer->SetText(L"������ �ü�ü\nHello World!");
	_textRenderer->SetFontColor(1.f, 0.f, 0.f, 1.f);

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

	/*Engine::Math::Vector3 tempPostion = _transform.position;
	tempPostion.z -= 300.f;
	tempPostion.y += 300.f;
	_camera.SetPosition(tempPostion);
	_camera.SetRotation(Engine::Math::Vector3(45.f, 0.f, 0.f));*/
}

void Player::PostFixedUpdate()
{

}