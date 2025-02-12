#pragma once

class MainCanvas;

namespace GameClient
{
	class Application final : public Engine::Application
	{
	public:
		explicit Application(HINSTANCE instanceHandle);

	protected:
		void LoadData(Engine::Load::IManager* loadManager) override;
		void DeclareInputActions(Engine::Input::IManager* inputManager) override;
		void Register(Engine::Content::IManager* contentManager, Engine::Load::IManager* loadManager) override;
		void PrepareInitialWorld(Engine::Content::Factory::World* worldFactory) override;
		void PrepareInitialHUD(Engine::DSHHud::Manager* hudManager) override;

	private:
		void DeclareUIAction(Engine::Input::IManager* inputManager, Engine::Input::IMappingContext* mappingContext);
		void DeclareMoveAction(Engine::Input::IManager* inputManager, Engine::Input::IMappingContext* mappingContext);
		void DeclareCameraAction(Engine::Input::IManager* inputManager, Engine::Input::IMappingContext* mappingContext);
		void DeclareSystemAction(Engine::Input::IManager* inputManager, Engine::Input::IMappingContext* mappingContext);


		MainCanvas* _mainCanvas;

	private:
		template<typename T>
		inline void RegisterHelp(const std::wstring& name, Engine::Load::IManager* loadManager, Engine::Content::Factory::Object* const objectFactory)
		{
			auto buildingConfig = loadManager->GetObjectRegisterData(name).value();
			auto buildingProperty = buildingConfig.GetProperty<std::filesystem::path>(L"fbxPath").value();

			objectFactory->Register<T>(buildingProperty.wstring(), buildingProperty.wstring());
		};
	};
}
