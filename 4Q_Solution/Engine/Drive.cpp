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

	if (oldWorld != nullptr) *oldWorld = _world;
	if (_world != nullptr) _world->Detach();
	_world = newWorld;
	if (_world != nullptr) _world->Attach();
}

void Engine::Drive::AttachHUD(HUD* newHUD, HUD** oldHUD)
{
	constexpr Utility::ThrowIfFailed thrower;

	if (oldHUD != nullptr) 	*oldHUD = _hud;
	if (_hud != nullptr) {} // TODO: Detach HUD
	_hud = newHUD;
	if (_hud != nullptr) {} // TODO: Attach HUD
}
