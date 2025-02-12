#include "pch.h"
#include "BaseWoolball.h"

int BaseWoolball::index = 0;
const int BaseWoolball::initPosition[6] = { 3,1,1,2,3,1 };
const int BaseWoolball::initDirection[6] = { -1,1,1,1,-1,1 };
const int BaseWoolball::thirdPos[6] = { 13.5, 13, 12.5, 12.5, 13, 13.5 };
const int BaseWoolball::muteValue[6] = { 3, 1, 2, 1, 2, 2 };

BaseWoolball::BaseWoolball(const std::filesystem::path& meshPath, const std::filesystem::path& physicsPath) :
	InteractObject(meshPath, meshPath),
	_pos{ }, _index{ index++ }, _activate{ false }
{
	_pos[0] = 0;
	_pos[1] = 7;
	_pos[2] = thirdPos[_index];

	_direction = initDirection[_index];
	_posIndex = initPosition[_index];
}

void BaseWoolball::Prepare(Engine::Content::Factory::Component* componentFactory)
{
	InteractObject::Prepare(componentFactory);
	_sync = componentFactory->Clone<Engine::Component::Synchronize>(this);
	_sound1 = componentFactory->Clone<Engine::Component::Effect3DSound>(this);
	_sound2 = componentFactory->Clone<Engine::Component::Effect3DSound>(this);
	_sound3 = componentFactory->Clone<Engine::Component::Effect3DSound>(this);
}

void BaseWoolball::SendInteractToServer()
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

void BaseWoolball::PreSetSoundProperty(int index, std::filesystem::path path)
{
	switch (index) {
	case 1:
		_sound1->SetPath(path);
		break;
	case 2:
		_sound2->SetPath(path);
		break;
	case 3:
		_sound3->SetPath(path);
		break;
	}
}

void BaseWoolball::PostSetSoundProperty(int index, float min, float max)
{
	switch (index) {
	case 1:
		_sound1->SetMaxDistance(max);
		_sound1->SetMinDistance(min);
		_sound1->SetPosition(_transform.position);
		break;
	case 2:
		_sound2->SetMaxDistance(max);
		_sound2->SetMinDistance(min);
		_sound2->SetPosition(_transform.position);
		break;
	case 3:
		_sound3->SetMaxDistance(max);
		_sound3->SetMinDistance(min);
		_sound3->SetPosition(_transform.position);
		break;
	}
}

void BaseWoolball::DisposeComponents()
{
	InteractObject::DisposeComponents();

	_sync->Dispose();
	_sound1->Dispose();
	_sound2->Dispose();
	_sound3->Dispose();
}

void BaseWoolball::PreInitialize(const Engine::Modules& modules)
{
	InteractObject::PreInitialize(modules);
	_sync->AddCallback((short)PacketID::InteractObject, &BaseWoolball::InteractCallback, this);
	myManager = modules.gameStateManager->FindSubManager(L"puzzle_01");
	myManager->Subscribe(L"Data", [this](const std::wstring& name, const std::any& value)
		{
			DataChangeCallBack(name, value);
		}
	, this);
}

void BaseWoolball::InteractCallback(const PlayMsg::InteractObject* msg)
{
	_posIndex += _direction;
	if (_posIndex == 2 || _posIndex == 0)
		_direction *= -1;
	auto isData = GameClient::Application::GetGameStateManager()->GetData(L"GameCoreData");
	if (!isData)
		return;
	auto data = std::any_cast<GameCoreData>(*isData);
	if (data.player == static_cast<int>(PlayerEnum::Live) || data.player == static_cast<int>(PlayerEnum::Developer))
	{
		if (_posIndex != muteValue[_index])
		{
			// 사운드 인덱스 재생
			switch (_index) {
			case 0:
				_sound1->Play();
				break;
			case 1:
				_sound2->Play();
				break;
			case 2:
				_sound3->Play();
				break;
			}
		}
	}
}
