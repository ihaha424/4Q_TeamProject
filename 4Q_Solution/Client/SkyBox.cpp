#include "pch.h"
#include "SkyBox.h"

SkyBox::SkyBox(std::filesystem::path&& meshPath)
	: _meshPath(std::move(meshPath))
	, _skyBox(nullptr)
{
}

void SkyBox::Prepare(Engine::Content::Factory::Component* componentFactory)
{
	_skyBox = componentFactory->Clone<Engine::Component::SkyBox>(this);
}

void SkyBox::DisposeComponents()
{
	_skyBox->Dispose();
}

void SkyBox::PreInitialize(const Engine::Modules& modules)
{
	Object::PreInitialize(modules);

	_skyBox->SetFilePath(_meshPath);
	_skyBox->SetMatrix(&_worldMatrix);
	_worldMatrix = Engine::Math::Matrix::CreateScale(5.f);
}

void SkyBox::PostInitialize(const Engine::Modules& modules)
{
	_skyBox->SetSkyBoxTexture(L"Assets/Textures/EnvHDR.dds");
	_skyBox->SetDiffuseTexture(L"Assets/Textures/DiffuseHDR.dds");
	_skyBox->SetBRDFTexture(L"Assets/Textures/Brdf.dds");
	_skyBox->SetSpecularTexture(L"Assets/Textures/SpecularHDR.dds");	
	_skyBox->SetPostEffectFlag(1);
}
