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

		virtual void Initialize();
		virtual void Attach();
		virtual void Update(float deltaTime);
		virtual void FixedUpdate();
		virtual void Detach();
		virtual void Finalize();
		
	protected:
		void LoadWorldFromFile(std::filesystem::path filePath);

	private:
		std::vector<Object*> _objects;
	};
}
