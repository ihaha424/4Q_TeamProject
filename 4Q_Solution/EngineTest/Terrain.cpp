#include "pch.h"
#include "Terrain.h"

Terrain::Terrain()
	: _staticMesh(L"../Resources/Level/Level.fbx", &_matrix)
{
}

void Terrain::Addition()
{
	Object::Addition();

	AddComponent(&_staticMesh);
}

void Terrain::PostInitialize()
{
	_matrix = Engine::Math::Matrix::CreateTranslation(0.f, 0.f, 0.f);
}
