#pragma once

namespace Engine::Component
{
    class SkeletalMesh;
    class Animator : public GraphicsComponent
    {
    public:
        Animator(SkeletalMesh* skeletalMesh);

    public:
        void Initialize() override;
        void Attach() override;
        void Detach() override;
        void Finalize() override;

    public:
        void ChangeAnimation(const char* animation) const;
        void ChangeAnimation(const char* animation, const unsigned int ID) const;
        bool IsLastFrame(float interval) const;
        void SetUpSplitBone(const unsigned int maxSplit) const;
        void SplitBone(const unsigned int ID, const char* boneName) const;

    private:
        SkeletalMesh* _skeletalMesh;
        GE::IAnimator* _geAnimator;
    };
}
