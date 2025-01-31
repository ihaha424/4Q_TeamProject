#include "pch.h"
#include "PhysicsSceneExample.h"

void PhysicsSceneExample::Prepare(Engine::Content::Factory::Object* objectFactory)
{
}

void PhysicsSceneExample::PreInitialize(const Engine::Modules& moduels)
{
	// 메인 씬 만들기 - 중력값 설정 필요
	Engine::Physics::SceneDesc mainSceneDesc{ {0.f,-9.8f,0.f},0 };
	Engine::Application::GetPhysicsManager()->CreateScene(&mainScene, mainSceneDesc);
	Engine::Application::GetPhysicsManager()->AttachUpdateSecne(mainScene);

	// 카메라 씬 만들기 - 중력값X
	Engine::Physics::SceneDesc cameraSceneDesc{ {0.f,0.f,0.f},0 };
	Engine::Application::GetPhysicsManager()->CreateCameraScene(&cameraScene, cameraSceneDesc);
}

void PhysicsSceneExample::PreUpdate(float deltaTime)
{

}

void PhysicsSceneExample::PostUpdate(float deltaTime)
{
	// 아마 Application에서 추가적으로 단꼐를 만들어서 해야 할듯 단꼐적으로는 이 위치가 맞음
	// 오브젝트들의 움직임이 끝나고 업데이트
	// 카메라 씬 업데이트(처음에 그려주고 마지막에 확인을 하기 때문에 따로 Attach를 해주지 않고 한다.)
	Engine::Application::GetPhysicsManager()->UpdateSecne(cameraScene, deltaTime);

	// 아마 Application에서 추가적으로 단꼐를 만들어서 해야 할듯 단꼐적으로는 이 위치가 맞음
	// 카메라 씬
	Engine::Application::GetPhysicsManager()->FetchSecne(cameraScene, true);


	Engine::Physics::AdditionalQueryData OverlapInfo;
	Engine::Physics::GeometryDesc geometryDesc;
	geometryDesc.type = Engine::Physics::GeometryShape::Frustum;
	//	Frustum data는 카메라 데이터
	//	data.x : fovY
	//	data.y : aspect
	//	data.z : nearPlane
	//	data.w : farPlane
	geometryDesc.data;
	Engine::Physics::VerticesMeshDesc verticesMeshDesc;
	Engine::Transform transform; // GetCameraTransform 해서 넣어줘야함
	cameraScene->Overlap(OverlapInfo, "Camera", geometryDesc, verticesMeshDesc, transform);

	// 카메라 컬링 된 오브젝트들의 포인터
	// 현제는 Component::Rigid->_boundBox의 포인터임 일단 Get,Get해서 Object의 포인터는 접근 가능 할 듯
	OverlapInfo.UserDatas;
}
