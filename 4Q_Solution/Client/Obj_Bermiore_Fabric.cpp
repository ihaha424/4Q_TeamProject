#include "pch.h"
#include "Obj_Bermiore_Fabric.h"

Obj_Bermiore_Fabric::Obj_Bermiore_Fabric(const std::filesystem::path& meshPath, const std::filesystem::path& physicsPath)
	: InteractObject(meshPath, physicsPath), _activate{ false }, _answer{false}
{
}

void Obj_Bermiore_Fabric::Prepare(Engine::Content::Factory::Component* componentFactory)
{
	InteractObject::Prepare(componentFactory);
	_sync = componentFactory->Clone<Engine::Component::Synchronize>(this);
	_sound = componentFactory->Clone<Engine::Component::Effect3DSound>(this);
	_soundClear = componentFactory->Clone<Engine::Component::Effect3DSound>(this);
}

void Obj_Bermiore_Fabric::SendInteractToServer()
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

void Obj_Bermiore_Fabric::SetActive(const PlayMsg::ObjectActive* msg)
{
	_activate = true;
	auto isdata = myManager->GetData(L"Data");
	if (isdata)
	{
		auto data = std::any_cast<Puzzle_01>(*isdata);
		data._puzzleClear = true;
		myManager->SetData(L"Data", data);
	}
}

void Obj_Bermiore_Fabric::InteractCallback(const PlayMsg::InteractObject* msg)
{
	auto isData = GameClient::Application::GetGameStateManager()->GetData(L"GameCoreData");
	if (!isData)
		return;
	auto data = std::any_cast<GameCoreData>(*isData);
	if (data.player == static_cast<int>(PlayerEnum::Live) || data.player == static_cast<int>(PlayerEnum::Developer))
	{
		// Sound ÆÄÀÏ
		_sound->Play();
	}
	
}

void Obj_Bermiore_Fabric::DisposeComponents()
{
	InteractObject::DisposeComponents();
	_sync->Dispose();
	_sound->Dispose();
	_soundClear->Dispose();
}

void Obj_Bermiore_Fabric::PreInitialize(const Engine::Modules& modules)
{
	InteractObject::PreInitialize(modules);
	myManager = modules.gameStateManager->FindSubManager(L"puzzle_01");
	_sync->AddCallback((short)PacketID::ObjectActive, &Obj_Bermiore_Fabric::SetActive, this);
	_sync->AddCallback((short)PacketID::InteractObject, &Obj_Bermiore_Fabric::InteractCallback, this);
	_sync->SetSerialNumber(12101);
	myManager->Subscribe(L"Data", [this](const std::wstring& name, const std::any& value)
		{
			DataChangeCallBack(name, value);
		}
	, this);

	_sound->SetPath(L"Assets/Sounds/SFX_Bermiore.wav");
	_soundClear->SetPath(L"Assets/Sounds/SFX_Bermiore_Clear.wav");
}

void Obj_Bermiore_Fabric::PostInitialize(const Engine::Modules& modules)
{
	InteractObject::PostInitialize(modules);

	_sound->SetMinDistance(10.f);
	_sound->SetMaxDistance(20.f);
	_sound->SetPosition(_transform.position);
	_soundClear->SetMinDistance(10.f);
	_soundClear->SetMaxDistance(20.f);
	_soundClear->SetPosition(_transform.position);

	_matrix = _transform.GetMatrix();
}

void Obj_Bermiore_Fabric::Interact()
{
	if (_activate)
		SendInteractToServer();
}

void Obj_Bermiore_Fabric::DataChangeCallBack(const std::wstring& name, const std::any& value)
{
	auto data = std::any_cast<Puzzle_01>(value);
	if (data._start)
		_activate = true;
	if (data._puzzleClear)
		_answer = true;
	if (data._finish) {
		_activate = false;
		_soundClear->Play();
	}
}
