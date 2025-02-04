#include "pch.h"
#include "Player.h"
#include "NetworkTemp.h"

Player::Player() :
	_camera(L"MainCamera", 1.f, 1000.f, { 16,9 }, 3.141592f / 4) // TODO: Remove this.
	//, _staticMesh(L"../Resources/FBX/char.fbx", &_worldMatrix)
	, _skeltalMesh(L"../Resources/Player/Player.X", &_worldMatrix)
	, _animator(&_skeltalMesh)
	, _textRenderer(L"../Resources/Font/±Ã¼­12.sfont"),
	_sync()
	, _rigid{}
	, _tempOtherRigid{}
{
}

void Player::Addition()
{
	Object::Addition();
	AddComponent(&_movement);
	AddComponent(&_camera);
	//AddComponent(&_staticMesh);
	AddComponent(&_skeltalMesh);
	AddComponent(&_animator);
	AddComponent(&_textRenderer);
	AddComponent(&_sync);
	AddComponent(&_rigid);
	AddComponent(&_tempOtherRigid);
}

void Player::PreInitialize()
{
	Object::PreInitialize();

	_movement.SetTarget(&_transform);

	_sync.SetSerialNumber(1);

	const auto inputManager = Engine::Application::GetInputManager();
	Engine::Input::IMappingContext* mappingContext = nullptr;
	inputManager->GetMappingContext(L"Default", &mappingContext);

	Engine::Input::IAction* moveAction = nullptr;
	mappingContext->GetAction(L"Move", &moveAction);
	moveAction->AddListener(Engine::Input::Trigger::Event::Triggered, [this](auto value)
	{
		Engine::Math::Vector3 direction = _movement.GetDirection();
		if (direction != Engine::Math::Vector3(value)) {
			_movement.SetDirection(value);		
			
			
			_sync._move.set_x(value.x);
			_sync._move.set_y(value.y);
			_sync._move.set_z(value.z);
			_sync._move.set_speed(_movement.GetSpeed());

			_sync._move.SerializeToString(&_sync._msgBuffer);

			Engine::Application::GetNetworkManager()->SaveSendData(
				(short)PacketID::Move,
				_sync._msgBuffer,
				_sync._move.ByteSizeLong(),
				_sync.GetSerialNumber()
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
		_animator.ChangeAnimation("Run"); 

		_sync._stateChange.set_stateinfo(1);
		_sync._stateChange.SerializeToString(&_sync._msgBuffer);

		Engine::Application::GetNetworkManager()->SaveSendData(
			(short)PacketID::StateChange,
			_sync._msgBuffer,
			_sync._stateChange.ByteSizeLong(),
			_sync.GetSerialNumber()
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
			_animator.ChangeAnimation("Wait"); 
			_movement.SetDirection(Engine::Math::Vector3::Zero);

			_sync._stateChange.set_stateinfo(0);
			_sync._stateChange.SerializeToString(&_sync._msgBuffer);

			Engine::Application::GetNetworkManager()->SaveSendData(
				(short)PacketID::StateChange,
				_sync._msgBuffer,
				_sync._stateChange.ByteSizeLong(),
				_sync.GetSerialNumber()
			);

			//NetworkTemp::GetInstance()->_stateChange.set_serialnumber(1);
			//NetworkTemp::GetInstance()->_stateChange.set_stateinfo(0);

			//Client::SavePacketData(
			//	NetworkTemp::GetInstance()->_stateChange.SerializeAsString(),
			//	(short)PacketID::StateChange,
			//	NetworkTemp::GetInstance()->_stateChange.ByteSizeLong());
			_movement.SetDirection(Engine::Math::Vector3::Zero);
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
		_camera.Rotate(value);
	});


	Engine::Physics::RigidComponentDesc desc;
	desc.rigidType = Engine::Physics::RigidBodyType::Dynamic;
	desc.shapeDesc.geometryDesc.type = Engine::Physics::GeometryShape::Capsule;
	desc.shapeDesc.geometryDesc.data = { 100.f, 100.f, 100.f };
	desc.shapeDesc.isExclusive = true;
	desc.shapeDesc.materialDesc.data = { 0.5f,0.5f,0.f };
	auto PhysicsManager = Engine::Application::GetPhysicsManager();


	PhysicsManager->CreateDynamic(&_rigid._rigidComponent, desc, Engine::Transform{}, 1.f, Engine::Transform{});
	PhysicsManager->GetScene(0)->AddActor(_rigid._rigidComponent);
	_rigid._rigidComponent->SetTranslate({ 0.f, 500.f, 0.f });

	_rigid._rigidComponent->BindCollision(std::bind(&Player::OnHit, this, std::placeholders::_1), Engine::Physics::ContactType::OnHit);

	desc.shapeDesc.geometryDesc.type = Engine::Physics::GeometryShape::Box;
	Engine::Transform tempTransform{};
	tempTransform.position.y = 500.f;
	PhysicsManager->CreateDynamic(&_tempOtherRigid._rigidComponent, desc, tempTransform, 1.f, Engine::Transform{});
	PhysicsManager->GetScene(0)->AddActor(_tempOtherRigid._rigidComponent);
}

void Player::PostInitialize()
{
	_movement.SetSpeed(100.f);	
	_textRenderer.SetPosition(100, 100.f);
	_textRenderer.SetText(L"ÁøÁöÇÑ ±Ã¼­Ã¼\nHello World!");
	_textRenderer.SetFontColor(1.f, 0.f, 0.f, 1.f);

	//_skeltalMesh.SetRenderLayer(0);
	/*_animator.SetUpSplitBone(2);
	_animator.SplitBone(0, "Dummy_root");
	_animator.SplitBone(1, "Bip01-Spine1");
	_animator.ChangeAnimation("Wait");*/

}

void Player::PostAttach()
{
	Object::PostAttach();
	_camera.Activate();	
}

void Player::PostUpdate(float deltaTime)
{	
	_worldMatrix = Engine::Math::Matrix::CreateScale(1.f) * Engine::Math::Matrix::CreateTranslation(_transform.position.x, _transform.position.y, _transform.position.z);

	/*Engine::Math::Vector3 tempPostion = _transform.position;
	tempPostion.z -= 300.f;
	tempPostion.y += 300.f;
	_camera.SetPosition(tempPostion);
	_camera.SetRotation(Engine::Math::Vector3(45.f, 0.f, 0.f));*/

	auto PhysicsManager = Engine::Application::GetPhysicsManager();

	Engine::Physics::AdditionalQueryData raycastInfo;
	PhysicsManager->GetScene(0)->Raycast(raycastInfo, { 0,1000,0 }, { 0,-1,0 }, 5000.f);
	Engine::Physics::AdditionalQueryData OverlapInfo;
	Engine::Physics::GeometryDesc geometryDesc;
	geometryDesc.type = Engine::Physics::GeometryShape::Frustum;
	Engine::Physics::VerticesMeshDesc verticesMeshDesc;
	Engine::Transform transform;
	PhysicsManager->GetScene(0)->Overlap(OverlapInfo, "camera", geometryDesc, verticesMeshDesc, transform);
}

void Player::PostFixedUpdate()
{

}

void Player::OnHit(Engine::Physics::ContactEvent info)
{
	info.myCollision
	info.otherCollision;
}

//RemotePlayer::RemotePlayer()
//	: _skeltalMesh(L"../Resources/Player/Player.X", &_worldMatrix)
//	, _animator(&_skeltalMesh)
//{
//}
//
//void RemotePlayer::Addition()
//{
//	Object::Addition();
//	AddComponent(&_skeltalMesh);
//	AddComponent(&_animator);
//}
