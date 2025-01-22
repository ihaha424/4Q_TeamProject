#pragma once
#include "Mesh.h"

namespace Engine::Component
{    
    class SkeletalMesh : public Mesh
    {
        friend class Animator;
    public:
        SkeletalMesh(std::filesystem::path filePath, Engine::Math::Matrix* matrix);

    public:
        void Initialize() override;  
    };
}
