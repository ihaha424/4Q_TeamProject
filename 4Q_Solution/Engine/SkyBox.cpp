#include "pch.h"
#include "SkyBox.h"
#include "GEGraphicsManager.h"

Engine::Component::SkyBox::SkyBox()
	: _geSkyBox(nullptr)
{
}

void Engine::Component::SkyBox::Initialize(const Modules& modules)
{
	Mesh::Initialize(modules);
	GE::MESH_RENDERER_DESC desc
	{
		.filePath = _filePath.c_str(),
		.type = GE::MESH_RENDERER_DESC::Type::SkyBox
	};

	auto renderSystem = _graphicsManager->GetRenderSystem();
	renderSystem->CreateMeshRenderer(&_geMeshRenderer, &desc);

	_geMeshRenderer->Query((void**)&_geSkyBox);
}

void Engine::Component::SkyBox::SetSkyBoxTexture(const wchar_t* filePath)
{
	_geSkyBox->SetSkyBoxTexture(filePath);
}

void Engine::Component::SkyBox::SetBRDFTexture(const wchar_t* filePath)
{
	_geSkyBox->SetBRDFTexture(filePath);
}

void Engine::Component::SkyBox::SetDiffuseTexture(const wchar_t* filePath)
{
	_geSkyBox->SetDiffuseTexture(filePath);
}

void Engine::Component::SkyBox::SetSpecularTexture(const wchar_t* filePath)
{
	_geSkyBox->SetSpecularTexture(filePath);
}