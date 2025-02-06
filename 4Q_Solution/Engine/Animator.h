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
        void ChangeAnimation(const char* animation, const unsigned int id) const;
        bool IsLastFrame(float interval, const unsigned int id = 0) const;
        void SetUpSplitBone(const unsigned int maxSplit) const;
        void SplitBone(const unsigned int id, const char* boneName) const;
        void SetAnimationSpeed(float speed) const;

    private:
        SkeletalMesh* _skeletalMesh;
        GE::IAnimator* _geAnimator;
    };
}
