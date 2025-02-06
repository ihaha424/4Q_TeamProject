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

	_worldMatrix = Engine::Math::Matrix::CreateTranslation(Engine::Math::Vector3(0.f, 2500.f, 0.f));
}

void SkyBox::PostInitialize(const Engine::Modules& modules)
{
	_skyBox->SetSkyBoxTexture(L"../Resources/IBL/EnvHDR.dds");
	_skyBox->SetDiffuseTexture(L"../Resources/IBL/DiffuseHDR.dds");
	_skyBox->SetBRDFTexture(L"../Resources/IBL/Brdf.dds");
	_skyBox->SetSpecularTexture(L"../Resources/IBL/SpecularHDR.dds");	
	_skyBox->SetPostEffectFlag(1);
}
