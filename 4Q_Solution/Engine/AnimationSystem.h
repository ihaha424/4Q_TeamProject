#pragma once

namespace Engine::Manager::GraphicsSystem
{
	struct IAnimationSystem
	{
		IAnimationSystem() = default;
		IAnimationSystem(const IAnimationSystem& other) = default;
		IAnimationSystem(IAnimationSystem&& other) noexcept = default;
		IAnimationSystem& operator=(const IAnimationSystem& other) = default;
		IAnimationSystem& operator=(IAnimationSystem&& other) noexcept = default;
		virtual ~IAnimationSystem() = default;
		
		virtual void CreateAnimator(GE::IMeshRenderer* meshRenderer, GE::IAnimator** outAnimator) const = 0;
		virtual void RegisterAnimator(GE::IAnimator* animator) const = 0;
		virtual void UnRegisterAnimator(GE::IAnimator* animator) const = 0;
	};

	class AnimationSystem final : public IAnimationSystem
	{
	public:
		AnimationSystem() = default;

		void Initialize(GE::IAnimationSystem* animationSystem, unsigned int threadCount);
		void Update(float deltaTime) const;
		void Finalize();

		void CreateAnimator(GE::IMeshRenderer* meshRenderer, GE::IAnimator** outAnimator) const override;
		void RegisterAnimator(GE::IAnimator* animator) const override;
		void UnRegisterAnimator(GE::IAnimator* animator) const override;

	private:
		GE::IAnimationSystem* _animationSystem;
	};
}