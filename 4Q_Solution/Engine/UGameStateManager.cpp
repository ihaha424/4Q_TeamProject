#include "pch.h"
#include "UGameStateManager.h"

Engine::UGameState::Manager::Manager()
	: datas{}, subscribers{}, subManagers{}
{
}



/*****************************
		DataObserver
 *****************************/
void Engine::UGameState::Manager::RegisterData(const std::wstring& dataName, std::any data)
{
	datas[dataName] = data;
}

void Engine::UGameState::Manager::SetData(const std::wstring& dataName, std::any newValue)
{
	if (datas.find(dataName) != datas.end())
	{
		datas[dataName] = newValue;
		NotifySubscribers(dataName);
	}
}

std::optional<std::any> Engine::UGameState::Manager::GetData(const std::wstring& dataName)
{
	if (datas.find(dataName) != datas.end())
		return datas.at(dataName);
	return std::nullopt;
}

void Engine::UGameState::Manager::Subscribe(const std::wstring& dataName, Callback callback, CallbackID subscriber)
{
	subscribers[dataName].emplace_back(subscriber, std::move(callback));
}

void Engine::UGameState::Manager::Unsubscribe(const std::wstring& dataName, CallbackID id)
{
	if (subscribers.find(dataName) != subscribers.end()) 
	{
		auto& functionVec = subscribers[dataName];
		functionVec.erase(std::remove_if(functionVec.begin(), functionVec.end(), 
				[id](const auto& pair) 
				{
					return pair.first == id;
				})
				, functionVec.end());
	}
}

void Engine::UGameState::Manager::NotifySubscribers(const std::wstring& dataName)
{
	if (subscribers.find(dataName) != subscribers.end())
	{
		for (const auto& [id, callback] : subscribers[dataName])
		{
			callback(dataName, datas[dataName]);
		}
	}
}


/*****************************
		SubManager
 *****************************/
void Engine::UGameState::Manager::RegisterSubManager(const std::wstring& managerName, IManager* subManager)
{
	subManagers[managerName] = subManager;
}

void Engine::UGameState::Manager::UnregisterSubManager(const std::wstring& managerName)
{
	if (subManagers.find(managerName) != subManagers.end())
	{
		subManagers[managerName] = nullptr;
	}
}

Engine::GameState::IManager* Engine::UGameState::Manager::FindSubManager(const std::wstring& managerName)
{
	if (subManagers.find(managerName) != subManagers.end())
	{
		return subManagers[managerName];
	}
	return nullptr;
}

Engine::GameState::IManager* Engine::UGameState::Manager::NewSubManager()
{
	Engine::GameState::IManager* newManager = new UGameState::Manager();
	return newManager;
}



/*****************************
		Engine
 *****************************/
void Engine::UGameState::Manager::Initialize()
{
}

void Engine::UGameState::Manager::Update(float deltaTime)
{
}

void Engine::UGameState::Manager::Finalize()
{
	datas.clear();
	subscribers.clear();
	for (auto node : subManagers)
		delete node.second;
	subManagers.clear();
}