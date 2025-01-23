#pragma once

namespace Engine::Component
{    
    class Mesh : public GraphicsComponent
    {
    protected:
        Mesh(std::filesystem::path filePath, Engine::Math::Matrix* matrix);

    public:
        void Attach() override;
        void Detach() override;
        void Finalize() override;

    public:
        void SetRenderLayer(const unsigned int layer);

    protected:
        std::filesystem::path   _filePath;
        GE::Matrix4x4*          _geMatrix;
        GE::IMeshRenderer*      _geMeshRenderer;
    };
}