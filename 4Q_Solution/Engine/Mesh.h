#pragma once

namespace Engine::Component
{    
    class Mesh : public GraphicsComponent
    {
    protected:
        Mesh();

    public:
        void Attach() override;
        void Detach() override;
        void Finalize() override;

    public:
        void SetRenderLayer(unsigned int layer) const;
		void SetMatrix(Math::Matrix* matrix);
		void SetFilePath(const std::filesystem::path& filePath);

    protected:
        std::filesystem::path   _filePath;
        GE::Matrix4x4*          _geMatrix;
        GE::IMeshRenderer*      _geMeshRenderer;
    };
}