#pragma once
#include "Mesh.h"

namespace Engine::Component
{    
    class SkeletalMesh : public Mesh
    {
        friend class Animator;
    public:
        SkeletalMesh() = default;

    public:
        void Initialize(const Modules& modules) override;  
    };
}
