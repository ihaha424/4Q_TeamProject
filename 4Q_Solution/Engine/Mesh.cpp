#include "pch.h"
#include "Mesh.h"

Engine::Component::Mesh::Mesh(std::filesystem::path filePath)
	: _filePath(std::move(filePath))
	, _matrix(nullptr)
	, _renderer(nullptr)
	, _layer(0)
{
	/*Engine::Application::GetGraphicsManager()->GetRenderSystem()->CreateMatrix(&_matrix);

	GE::MESH_RENDERER_DESC desc
	{
		.filePath = filePath.c_str(),
		.type = GE::MESH_RENDERER_DESC::Type::Static
	};

	Engine::Application::GetGraphicsManager()->GetRenderSystem()->CreateMeshRenderer(&_renderer, &desc);*/
}

void Engine::Component::Mesh::Attach()
{
	Component::Attach();
	//Engine::Application::GetGraphicsManager()->GetRenderSystem()->RegisterRenderQueue(_layer, _renderer, _matrix);
}

void Engine::Component::Mesh::Detach()
{
	Component::Detach();
	//Engine::Application::GetGraphicsManager()->GetRenderSystem()->UnRegisterRenderQueue(_layer, _renderer);
}
