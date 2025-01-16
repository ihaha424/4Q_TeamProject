#pragma once

namespace Engine
{
	class World;
	class HUD;

	class Drive
	{
	public:
		Drive();

		void Update(float deltaTime) const;
		void FixedUpdate() const;

		void AttachWorld(World* newWorld, World** oldWorld);
		void AttachHUD(HUD* newHUD, HUD** oldHUD);

	private:
		World* _world;
		HUD* _hud;
	};
}

