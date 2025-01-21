#pragma once

namespace Engine::Component
{    
    class Mesh : public GraphicsComponent
    {
    protected:
        Mesh(std::filesystem::path filePath);

    public:
        void Attach() override;
        void Detach() override;
        void Finalize() override;

    protected:
        std::filesystem::path   _filePath;
        GE::IMatrix*            _geMatrix;
        GE::IMeshRenderer*      _geMeshRenderer;
        unsigned int            _layer;
    };
}