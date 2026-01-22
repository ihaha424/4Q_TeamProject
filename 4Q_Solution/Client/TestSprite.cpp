#include "pch.h"
#include "TestSprite.h"

TestSprite::TestSprite()
	: _sprite(nullptr)
{
}

void TestSprite::Prepare(Engine::Content::Factory::Component* componentFactory)
{
	_sprite = componentFactory->Clone<Engine::Component::Sprite>(this);
}

void TestSprite::DisposeComponents()
{
	_sprite->Dispose();
}

void TestSprite::PreInitialize(const Engine::Modules& modules)
{
	Object::PreInitialize(modules);

	_sprite->SetMatrix(&_worldMatrix);
	_sprite->SetFilePath(L"Assets/Sprites/test.png");

	// _worldMatrix = Engine::Math::Matrix::CreateRotationZ(3.14f);
}
