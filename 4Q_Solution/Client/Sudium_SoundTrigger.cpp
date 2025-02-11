#include "pch.h"
#include "Sudium_SoundTrigger.h"
#include "Application.h"

int Sudium_SoundTrigger::_settingIndex = 0;
Sudium_SoundTrigger::Sudium_SoundTrigger(const std::filesystem::path& meshPath, const std::filesystem::path& physicsPath)
	: TriggerArea(meshPath, meshPath)
{
}

void Sudium_SoundTrigger::Prepare(Engine::Content::Factory::Component* componentFactory)
{
	TriggerArea::Prepare(componentFactory);
	switch (_settingIndex)
	{
	case 0:
		//방향에 따른 음향 세팅값
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	}
	_settingIndex++;
}


void Sudium_SoundTrigger::PreInitialize(const Engine::Modules& modules)
{
	TriggerArea::PreInitialize(modules);
	_trigger->BindBeginInteraction([]() {
		auto isData = GameClient::Application::GetGameStateManager()->GetData(L"GameCoreData");
		if (!isData)
			return;
		auto data = std::any_cast<GameCoreData>(*isData);
		if (data.player == 2)
		{
			//sound ㄱㄱ
		}
		});

}

