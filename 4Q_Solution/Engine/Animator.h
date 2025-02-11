#pragma once

namespace Engine::Component
{
    class SkeletalMesh;
    class Animator : public GraphicsComponent
    {
    public:
        Animator() = default;

    public:
        void Initialize(const Modules& modules) override;
        void Attach() override;
        void Detach() override;
        void Finalize() override;

    public:
		void SetSkeletalMesh(SkeletalMesh* skeletalMesh);

        void ChangeAnimation(const char* animation) const;
        void ChangeAnimation(const char* animation, unsigned int id) const;
        void SyncPartialAnimation(unsigned int parentID, unsigned int childID) const;
        bool IsLastFrame(float interval, unsigned int id = 0) const;
        void SetUpSplitBone(unsigned int maxSplit) const;
        void SplitBone(unsigned int id, const char* boneName) const;
        void SetAnimationSpeed(float speed) const;
        void MakeParent(const char* parent, const char* child) const;
        void GetSkeletonMatrix(const char* bone, Engine::Math::Matrix** out) const;

    private:
        SkeletalMesh* _skeletalMesh;
        GE::IAnimator* _geAnimator;
    };
}
