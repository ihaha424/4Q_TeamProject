#pragma once
#include "includes/IAnimator.h"

class Skeleton;
class Transform;
class Animation;
struct Bone;

class Animator : public GE::IAnimator
{
	enum Type { Upper, Lower, End };
	struct Controller
	{
		const char* animation = "";
		float playTime = 0.f;
		float lastTime = 0.f;
	};

	struct BlendInfo
	{
		std::string prevAnimation;
		float prevPlayTime = 0.f;
		float blendTime = 0.f;
		bool isBlending = false;
	};

public:
	explicit Animator();
	virtual ~Animator() = default;

public:
	const std::vector<Matrix>& GetAnimationTransform() const { return _animationTransforms; }
	const unsigned int GetID() const { return _ID; }

public:
	void Intialize(const wchar_t* filePath, Skeleton* pSkeleton);
	void Update(const float deltaTime);

public:
	// IAnimator을(를) 통해 상속됨
	void Release() override;
	void ChangeAnimation(const char* animation) override;
	bool IsLastFrame(float interval) const override;

private:
	void UpdateAnimationTransform(const Bone& skeletion, const XMMATRIX& parentTransform, Controller* controller);
	XMVECTOR InterpolationVector3(const std::vector<std::pair<float, Vector3>>& v, const float t);
	XMVECTOR InterpolationVector4(const std::vector<std::pair<float, Vector4>>& v, const float t);
	XMMATRIX BlendAnimationMatrix(const XMMATRIX& matrix1, const XMMATRIX& matrix2, float t);

	template<typename T>
	unsigned int FindIndex(T& v, float animationTime)
	{
		unsigned int size = (unsigned int)v.size();
		for (unsigned int i = 0; i < size - 1; i++)
		{
			if (animationTime < v[i + 1].first)
				return i;
		}

		return size - 2;
	}

	void BoneMasking(const Bone& bone, int mask);

private:
	std::unordered_map<std::string, int>	_boneMask;
	Matrix									_root;
	BlendInfo								_blendInfo;
	std::vector<Matrix>						_animationTransforms;
	Controller								_controller[End];
	Controller								_prevController[End];
	std::shared_ptr<Animation>				_animation;
	Skeleton*								_pSkeleton{ nullptr };
	static unsigned int						_globalID;
	unsigned int							_ID{ 0 };
};