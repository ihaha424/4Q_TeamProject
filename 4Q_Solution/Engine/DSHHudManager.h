#pragma once

namespace Engine::DSHHud
{
	class Manager
	{
	public:
		Manager();

		void Initialize();
		void Finalize();

		void Contraction(const Modules& modules);
		void Update(float deltaTime) const;
		void FixedUpdate() const;
		void Relaxation();

		void SetCanvas(Canvas* canvas);

	private:
		Canvas* _canvas;
		Canvas* _nextCanvas;
	};
}
