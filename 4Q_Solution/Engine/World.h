#pragma once

namespace Engine
{
	class Object;

	class World
	{
	public:
		World() = default;
		World(const World& other) = default;
		World(World&& other) noexcept = default;
		World& operator=(const World& other) = default;
		World& operator=(World&& other) noexcept = default;
		virtual ~World() = default;

		void Setup(Modules modules); // Refactor this.
		void Initialize();
		void Attach();
		void Update(float deltaTime);
		void FixedUpdate();
		void Detach();
		void Finalize();
		
	protected:
		virtual void Addition(); // TODO: Remove this.
		virtual void PreInitialize();
		virtual void PostInitialize();
		virtual void PreAttach();
		virtual void PostAttach();
		virtual void PreUpdate(float deltaTime);
		virtual void PostUpdate(float deltaTime);
		virtual void PreFixedUpdate();
		virtual void PostFixedUpdate();
		virtual void PreDetach();
		virtual void PostDetach();
		virtual void PreFinalize();
		virtual void PostFinalize();

		void LoadWorldFromFile(const std::filesystem::path& filePath);

		void AddObject(Object* object); // TODO: Refactor

	private:
		std::vector<Object*> _objects;
	};
}
