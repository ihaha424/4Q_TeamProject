#include "pch.h"
#include "Obj_Bermiore_Soundblock.h"

Obj_Bermiore_Soundblock::Obj_Bermiore_Soundblock(const std::filesystem::path& meshPath, const std::filesystem::path& physicsPath)
	: InteractObject(meshPath, meshPath), _sync{ nullptr }
{
}

void Obj_Bermiore_Soundblock::Prepare(Engine::Content::Factory::Component* componentFactory)
{
	InteractObject::Prepare(componentFactory);
	_sync = componentFactory->Clone<Engine::Component::Synchronize>(this);
}

void Obj_Bermiore_Soundblock::SendInteractToServer()
{
	_sync->_interactObject.set_objectserialnumber(_sync->GetSerialNumber());
	_sync->_interactObject.SerializeToString(&_sync->_msgBuffer);
	Client::SavePacketData(
		_sync->_msgBuffer,
		(short)PacketID::InteractObject,
		_sync->_interactObject.ByteSizeLong(),
		_sync->GetSerialNumber()
	);
}

void Obj_Bermiore_Soundblock::PlaySound(const PlayMsg::InteractObject* msg)
{
	auto isData = GameClient::Application::GetGameStateManager()->GetData(L"GameCoreData");
	if (!isData)
		return;
	auto data = std::any_cast<GameCoreData>(*isData);
	if (data.player == static_cast<int>(PlayerEnum::Live) || data.player == static_cast<int>(PlayerEnum::Developer))
	{
		// 사운드 컴포먼트 6개를 1개씩 실행해야함
		// flag로 한다음 update에서 확인 하는 방식을 생각함
	}
}

void Obj_Bermiore_Soundblock::DisposeComponents()
{
	InteractObject::DisposeComponents();
	_sync->Dispose();
}

void Obj_Bermiore_Soundblock::PreInitialize(const Engine::Modules& modules)
{
	InteractObject::PreInitialize(modules);
	myManager = modules.gameStateManager->FindSubManager(L"puzzle_01");
	myManager->Subscribe(L"Data", [this](const std::wstring& name, const std::any& value)
{
			DataChangeCallBack(name, value);
		}
	, this);
	_sync->AddCallback((short)PacketID::InteractObject, &Obj_Bermiore_Soundblock::PlaySound, this);
	_sync->SetSerialNumber(12108);
}

void Obj_Bermiore_Soundblock::Interact()
{
	SendInteractToServer();
}

void Obj_Bermiore_Soundblock::DataChangeCallBack(const std::wstring& name, const std::any& value)
{
	auto data = std::any_cast<Puzzle_01>(value);
	if (data._finish)
		_activate = false;
	if (data._start)
		_activate = true;
}
