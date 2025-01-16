#include "pch.h"
#include "Drive.h"

Engine::Drive::Drive() :
	_world(nullptr),
	_hud(nullptr)
{
}

void Engine::Drive::Update(const float deltaTime) const
{
	if (_world != nullptr) _world->Update(deltaTime);
	// TODO: Update HUD
}

void Engine::Drive::FixedUpdate() const
{
	if (_world != nullptr) _world->FixedUpdate();
	// TODO: FixedUpdate HUD
}

void Engine::Drive::AttachWorld(World* newWorld, World** oldWorld)
{
	constexpr Utility::ThrowIfFailed thrower;

	if (oldWorld == nullptr) thrower(E_INVALIDARG);
	if (_world != nullptr) _world->Attach();
	*oldWorld = _world;
	_world = newWorld;
	if (_world != nullptr) _world->Detach();
}

void Engine::Drive::AttachHUD(HUD* newHUD, HUD** oldHUD)
{
	constexpr Utility::ThrowIfFailed thrower;

	if (oldHUD == nullptr) thrower(E_INVALIDARG);
	if (_hud != nullptr) {} // TODO: Attach HUD
	*oldHUD = _hud;
	_hud = newHUD;
	if (_hud != nullptr) {} // TODO: Detach HUD
}
