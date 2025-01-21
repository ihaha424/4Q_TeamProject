#pragma once

namespace Engine::Component
{
    class Animator : public Component
    {
    public:
        Animator();

    public:
        void ChangeAnimation(const char* animation) const;
        void ChangeAnimation(const char* animation, const unsigned int ID) const;
        bool IsLastFrame(float interval) const;
        void SetUpSplitBone(const unsigned int maxSplit) const;
        void SplitBone(const unsigned int ID, const char* boneName) const;

    private:
        GE::IAnimator* _animator;
    };
}
