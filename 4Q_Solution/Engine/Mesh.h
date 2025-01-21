#pragma once

namespace Engine::Component
{    
    class Mesh : public Component
    {
    protected:
        Mesh(std::filesystem::path filePath);

    public:
        void Attach() override;
        void Detach() override;

    protected:
        std::filesystem::path   _filePath;
        GE::IMatrix*            _matrix;
        GE::IMeshRenderer*      _renderer;
        unsigned int            _layer;
    };
}