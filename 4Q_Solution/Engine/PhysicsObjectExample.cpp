#include "pch.h"
#include "PhysicsObjectExample.h"

PhysicsObjectExample::PhysicsObjectExample()
{
}

void PhysicsObjectExample::Prepare(Engine::Content::Factory::Component* componentFactory)
{
	_rigid			= componentFactory->Clone<Engine::Component::Rigid>();
	_rigidStatic	= componentFactory->Clone<Engine::Component::RigidStatic>();
	_rigidDynamic	= componentFactory->Clone<Engine::Component::RigidDynamic>();
	_rigidKinematic = componentFactory->Clone<Engine::Component::RigidKinematic>();
}

void PhysicsObjectExample::DisposeComponents()
{
	_rigid->Dispose();
	_rigidStatic->Dispose();
	_rigidDynamic->Dispose();
	_rigidKinematic->Dispose();
}

void PhysicsObjectExample::PreInitialize(const Engine::Modules& modules)
{
	Object::PreInitialize(modules);

	auto PhysicsManager = Engine::Application::GetPhysicsManager();

	// Rigid, Static, Kinematic도 동일 //&& 부분만 신경써서 바꿔주면 됨
	// Example Dynamic
	{
		// 1. Description 만들기
		Engine::Physics::RigidComponentDesc desc;
		desc.rigidType = Engine::Physics::RigidBodyType::Dynamic;						//&&
		desc.shapeDesc.geometryDesc.type = Engine::Physics::GeometryShape::Capsule;
		desc.shapeDesc.geometryDesc.data = { 100.f, 100.f, 100.f };
		desc.shapeDesc.isExclusive = true;
		desc.shapeDesc.materialDesc.data = { 0.5f,0.5f,0.f };
		// 2. Transform 만들기
		Engine::Transform transform{};
		transform.position = { 0,0,0 };
		// 3. 객체 생성
		PhysicsManager->CreateDynamic(&_rigidDynamic->_rigidbody, desc, transform, 1);	//&&
		// 4. 씬에 넣기
		// 임시로 GetScene한 것   ->   World의 MainScene가져와서 초기화
		PhysicsManager->GetScene(0)->AddActor(_rigidDynamic->_rigidbody);

		// Pre5. 추가적으로 바운드 박스만 따로 만들어서 관리(다이나믹도 이것으로 할지 고민 중...)
		PhysicsManager->CreateStaticBoundBoxActor(&_rigidDynamic->_boundBox);
		// 5. 카메라 씬에 추가 :GetScene(1): 카메라 씬이라고 가정
		PhysicsManager->GetScene(1)->AddActor(_rigidDynamic->_boundBox);
	}
}

void PhysicsObjectExample::PreUpdate(float deltaTime)
{
	// 네트 워크를 통해 받든 뭘 받든 GetTransform();통해 위치 동기화
	// Response
	_rigidDynamic->_rigidbody->GetTransform();

	// Collision Check
	// 이 부분은 추후 Transform을 언제 어떻게 받아오고 보낼지에 따라 달라질듯
	// Component의 업데이트 부분도 바꿔야함
}

void PhysicsObjectExample::PostUpdate(float deltaTime)
{
	// 움직이는 물체일 경우에만 해줌
	_rigidDynamic->_boundBox->SetTransform(_rigidDynamic->_rigidbody->GetTransform());
}

void PhysicsObjectExample::PreFixedUpdate()
{

}

void PhysicsObjectExample::PostFixedUpdate()
{
}

void PhysicsObjectExample::SceneQueryExample()
{
	auto PhysicsManager = Engine::Application::GetPhysicsManager();

	// Raycast
	{
		Engine::Physics::AdditionalQueryData raycastInfo;
		/*
			Param	
				AdditionalQueryData	raycastInfo : 콜백 받을 raycast정보
				Vector3	startPosition			: 점의 시작 위치
				Vector3	direction				: 방향
				float	distance				: 최대 거리
		*/
		PhysicsManager->GetScene(0)->Raycast(raycastInfo, { 0,1000,0 }, { 0,-1,0 }, 5000.f);
	}

	// Overlap
	{
		Engine::Physics::AdditionalQueryData OverlapInfo;
		Engine::Physics::GeometryDesc geometryDesc;
		geometryDesc.type = Engine::Physics::GeometryShape::Frustum;
		Engine::Physics::VerticesMeshDesc verticesMeshDesc;
		Engine::Transform transform;
		/*
			Param
				Engine::Physics::QueryData&					overlapInfo			: 콜백받을 오버렙정보
				const std::string&							name				: 도형 이름
				const Engine::Physics::GeometryDesc&		geometryDesc		: 도형 디스크립션
				const Engine::Physics::VerticesMeshDesc&	verticesMeshDesc	: 정점 도형일 경우 추가 디스크립션
																				, 기본도형일 경우 그냥 빈 깡통을 넣어주면 됨
				const Engine::Transform&					transform			: 위치, 회전정보

			Brief
				: 만약 이미 만들어둔 도형이 있으면 이름으로 실행 할 수 있음.
				geometryDesc, verticesMeshDesc의 경우 이름으로 찾지 못할 경우 정보를 바탕으로 만들어짐.
		*/
		PhysicsManager->AddGeomtry("Frustum", geometryDesc, verticesMeshDesc);
		PhysicsManager->GetScene(0)->Overlap(OverlapInfo, "Frustum", transform);
	}

	// Sweep
	{
		Engine::Physics::AdditionalQueryData OverlapInfo;
		Engine::Physics::GeometryDesc geometryDesc;
		geometryDesc.type = Engine::Physics::GeometryShape::Frustum;
		Engine::Physics::VerticesMeshDesc verticesMeshDesc;
		Engine::Transform transform;
		Engine::Math::Vector3 direction;
		float distance = 1000.f;
		/*
			Param
				Engine::Physics::AdditionalQueryData&		sweepInfo				: 콜백받을 오버렙정보
				const std::string&							name 					: 도형 이름
				const Engine::Physics::GeometryDesc&		geometryDesc 			: 도형 디스크립션
				const Engine::Physics::VerticesMeshDesc&	verticesMeshDesc 		: 정점 도형일 경우 추가 디스크립션
																					, 기본도형일 경우 그냥 빈 깡통을 넣어주면 됨
				const Engine::Transform&					transform 				: 위치, 회전정보
				const Engine::Math::Vector3&				direction				: 방향
				float										distance				: 거리
		
			Brief
				: 만약 이미 만들어둔 도형이 있으면 이름으로 실행 할 수 있음.
				geometryDesc, verticesMeshDesc의 경우 이름으로 찾지 못할 경우 정보를 바탕으로 만들어짐.
		*/
		PhysicsManager->AddGeomtry("Frustum", geometryDesc, verticesMeshDesc);
		PhysicsManager->GetScene(0)->Sweep(OverlapInfo, "Frustum", transform, direction, distance);
	}
	// 도형 추가 옵션
	{
		Engine::Physics::GeometryDesc geometryDesc;
		geometryDesc.type = Engine::Physics::GeometryShape::Frustum;
		Engine::Physics::VerticesMeshDesc verticesMeshDesc;
		/**
		 * @brief	만드는데 성공하면 true,
					실패 또는 이미 있는 이름의 도형이면 false
		 */
		PhysicsManager->AddGeomtry("Frustum", geometryDesc, verticesMeshDesc);
	}

}
