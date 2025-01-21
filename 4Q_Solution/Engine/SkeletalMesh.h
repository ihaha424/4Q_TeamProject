#pragma once
#include "Mesh.h"

namespace Engine::Component
{
    class Animator;
    class SkeletalMesh : public Mesh
    {
    public:
        SkeletalMesh(std::filesystem::path filePath);

    public:
        Animator* GetAnimator() { return _animator; }

    public:
        void Initialize() override;

    private:
        Animator* _animator;
    };
}
