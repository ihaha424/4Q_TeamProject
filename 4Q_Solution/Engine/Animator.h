#pragma once

namespace Engine::Component
{
    class Animator : public GraphicsComponent
    {
    public:
        Animator();

    public:
        void Attach() override;
        void Detach() override;
        void Finalize() override;

    public:
        void SetAnimator(GE::IAnimator* geAnimator) { _geAnimator = geAnimator; }

    public:
        void ChangeAnimation(const char* animation) const;
        void ChangeAnimation(const char* animation, const unsigned int ID) const;
        bool IsLastFrame(float interval) const;
        void SetUpSplitBone(const unsigned int maxSplit) const;
        void SplitBone(const unsigned int ID, const char* boneName) const;

    private:
        GE::IAnimator* _geAnimator;
    };
}
