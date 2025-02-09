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
        void SetPostEffectFlag(unsigned int flag);
		void SetMatrix(Math::Matrix* matrix);
		void SetFilePath(const std::filesystem::path& filePath);
        void SetActiveDraw(bool isActive);
        void SetActiveShadow(bool isActive);

    protected:
        std::filesystem::path   _filePath;
        GE::Matrix4x4*          _geMatrix;
        GE::IMeshRenderer*      _geMeshRenderer;
        GE::MeshDescription     _geMeshDescription;
    };
}