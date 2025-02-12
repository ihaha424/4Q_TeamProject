#include "pch.h"
#include "Trigger_Sudium_SoundTrigger_1.h"
#include "Application.h"


Trigger_Sudium_SoundTrigger_1::Trigger_Sudium_SoundTrigger_1(const std::filesystem::path& meshPath, const std::filesystem::path& physicsPath)
	: TriggerArea(meshPath, meshPath)
{
}

void Trigger_Sudium_SoundTrigger_1::Prepare(Engine::Content::Factory::Component* componentFactory)
{
	TriggerArea::Prepare(componentFactory);
	_sync = componentFactory->Clone<Engine::Component::Synchronize>(this);
	_soundLeft = componentFactory->Clone<Engine::Component::EffectSound>(this);
}

void Trigger_Sudium_SoundTrigger_1::DisposeComponents()
{
	TriggerArea::DisposeComponents();
	_sync->Dispose();
	_soundLeft->Dispose();
}

void Trigger_Sudium_SoundTrigger_1::TriggerEvent(const PlayMsg::TriggerObject* msg)
{
	auto isData = GameClient::Application::GetGameStateManager()->GetData(L"GameCoreData");
	if (!isData)
		return;
	auto data = std::any_cast<GameCoreData>(*isData);
	if (data.player == 2 || data.player == 3)
	{
		_soundLeft->Play();
	}
}


void Trigger_Sudium_SoundTrigger_1::PreInitialize(const Engine::Modules& modules)
{
	TriggerArea::PreInitialize(modules);
	_sync->SetSerialNumber(8011);
	_sync->AddCallback((short)PacketID::TriggerObject, &Trigger_Sudium_SoundTrigger_1::TriggerEvent, this);

	_trigger->BindBeginInteraction([this]() {
		auto isData = GameClient::Application::GetGameStateManager()->GetData(L"GameCoreData");
		if (!isData)
			return;
		auto data = std::any_cast<GameCoreData>(*isData);
		if (data.player == 2 || data.player == 3)
		{
			//sound ¤¡¤¡
			_sync->_triggerObject.set_objectserialnumber(data.player);
			_sync->_triggerObject.set_triggerboxid(_sync->GetSerialNumber());
			_sync->_triggerObject.SerializeToString(&_sync->_msgBuffer);
			Engine::Application::GetNetworkManager()->SaveSendData(
				(short)PacketID::TriggerObject,
				_sync->_msgBuffer,
				_sync->_triggerObject.ByteSizeLong(),
				_sync->GetSerialNumber()
			);
		}
		});
	_soundLeft->SetPath(L"Assets/Sounds/SFX_Env_Sudium_Maze_Left.wav");
}

void Trigger_Sudium_SoundTrigger_1::PostInitialize(const Engine::Modules& modules)
{

}

