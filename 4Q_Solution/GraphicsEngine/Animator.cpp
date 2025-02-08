#include "pch.h"
#include "Animator.h"
#include "Skeleton.h"
#include "Animation.h"

unsigned int Animator::_globalID = 0;

Animator::Animator()
	: _ID(_globalID++)
	, _maxSplit(1)
{
}

void Animator::Initialize(const wchar_t* filePath, Skeleton* pSkeleton)
{
	_animation = g_pResourceMgr->LoadResource<Animation>(filePath);
	_animationTransforms.resize(MAX_BONE_MATRIX);
	_blendTransform.resize(MAX_BONE_MATRIX);
	_blendInfo.prevAnimation.resize(64);

	_pSkeleton = pSkeleton;	

	_controllers.resize(1);
	_prevControllers.resize(1);
}

void Animator::Update(const float deltaTime)
{
	XMMATRIX identity = XMMatrixIdentity();

	for (unsigned int i = 0; i < _maxSplit; i++)
	{
		const Animation::Channel& animation = _animation->_animations[_controllers[i].animation];

		_controllers[i].playTime += _speed * deltaTime;
	
		if (_controllers[i].playTime >= animation.lastTime)
		{
			_controllers[i].playTime = 0.f;
			//_root = XMMatrixIdentity();
		}

		/*XMMATRIX prevRoot = _root;*/


		/*if (5.f >= XMVector3Length(deltaPosition).m128_f32[0])
		{
			_pTransform->_position += XMVector3TransformCoord(deltaPosition, XMMatrixRotationY(_pTransform->_rotation.y + XM_PIDIV2));
		}*/
	}

	UpdateAnimationTransform(*_pSkeleton->GetBone(), identity, _controllers.data());

	/*XMVECTOR deltaPosition = XMVectorSubtract(_root.Translation(), prevRoot.r[3]);
	deltaPosition.m128_f32[1] = 0.f;*/

	if (_blendInfo.isBlending)
	{
		/*const Animation::Channel& prevAnimation = _animation->_animations[_blendInfo.prevAnimation];
		_blendInfo.prevPlayTime += _speed * deltaTime;

		if (_blendInfo.prevPlayTime > prevAnimation.lastTime)
			_blendInfo.prevPlayTime = 0.f;*/

		if (1.f <= _blendInfo.blendTime)
		{
			_blendInfo.blendTime = 0.f;
			_blendInfo.isBlending = false;
		}
		else
		{
			memcpy(_blendTransform.data(), _animationTransforms.data(), sizeof(Matrix) * MAX_BONE_MATRIX);
			UpdateAnimationTransform(*_pSkeleton->GetBone(), identity, _prevControllers.data());

			//float cubic = sqrt(1 - powf(_blendInfo.blendTime - 1.f, 2));
			float easing = 1 - (1 - _blendInfo.blendTime) * (1 - _blendInfo.blendTime);

			for (size_t i = 0; i < MAX_BONE_MATRIX; i++)
			{
				_animationTransforms[i] = BlendAnimation(_animationTransforms[i], _blendTransform[i], easing);
			}
		}

		_blendInfo.blendTime += deltaTime * 5.f;
	}
}

void Animator::Release()
{
	delete this;
}

void Animator::ChangeAnimation(const char* animation)
{
	auto iter = _animation->_animations.find(animation);
	if (iter == _animation->_animations.end())
		return;

	if (!strcmp(_controllers[0].animation, animation))
		return;

	memcpy(_blendInfo.prevAnimation.data(), _controllers[0].animation, strlen(_controllers[0].animation));
	_blendInfo.prevPlayTime = _controllers[0].playTime;
	_blendInfo.blendTime = 0.f;
	_blendInfo.isBlending = true;
	memcpy(_prevControllers.data(), _controllers.data(), sizeof(Controller) * _controllers.size());

	for (auto& controller : _controllers)
	{
		controller.animation = animation;
		controller.playTime = 0.f;
		controller.lastTime = iter->second.lastTime;
	}
}

void Animator::ChangeAnimation(const char* animation, const unsigned int ID)
{
	if (_animation->_animations.find(animation) == _animation->_animations.end())
		return;

	if (!strcmp(_controllers[ID].animation, animation))
		return;

	memcpy(_blendInfo.prevAnimation.data(), _controllers[ID].animation, strlen(_controllers[ID].animation) + 1);
	_blendInfo.prevPlayTime = _controllers[ID].playTime;
	_blendInfo.blendTime = 0.f;
	_blendInfo.isBlending = true;
	//memcpy(_prevControllers.data(), _controllers.data(), sizeof(Controller) * _controllers.size());
	_prevControllers[ID] = _controllers[ID];
	
	_controllers[ID].animation = animation;
	_controllers[ID].playTime = 0.f;
}

bool Animator::IsLastFrame(float interval, const unsigned int ID) const
{
	return _controllers[ID].playTime + interval > _controllers[ID].lastTime;
}

void Animator::SetUpSplitBone(const unsigned int maxSplit)
{
	_pSkeleton->SetUpSplitBone(maxSplit);
	_maxSplit = maxSplit;

	_controllers.resize(maxSplit);
	_prevControllers.resize(maxSplit);
}

void Animator::SplitBone(const unsigned int ID, const char* boneName)
{
	if (_maxSplit <= ID)
	{
		ASSERT(false, L"Greater than the number of bones you set.");
		return;
	}

	_pSkeleton->SplitBone(ID, boneName);
	BoneMasking(_pSkeleton->GetBone(ID), ID);
}

void Animator::SetAnimationSpeed(float speed)
{
	_speed = speed;
}

void Animator::MakeParent(const char* parent, const char* child)
{
	_pSkeleton->MakeParent(parent, child);
}

void Animator::UpdateAnimationTransform(Bone& skeletion,
										const XMMATRIX& parentTransform,
										Controller* pController)
{
	Controller& current = pController[_boneMask[skeletion.name]];
	auto iter = _animation->_animations[current.animation].boneTransforms.find(skeletion.name);
	
	XMMATRIX localTransform = skeletion.local;

	if (iter != _animation->_animations[current.animation].boneTransforms.end())
	{
		Animation::BoneTransformTrack& keyFrame = iter->second;
	
		XMMATRIX scale = XMMatrixScalingFromVector(InterpolationVector3(keyFrame.scales, current.playTime));
		XMMATRIX rotation = XMMatrixRotationQuaternion(InterpolationVector4(keyFrame.rotations, current.playTime));
		XMMATRIX position = XMMatrixTranslationFromVector(InterpolationVector3(keyFrame.positions, current.playTime));

		localTransform = scale * rotation * position;
		// skeletion.anim = localTransform;

		//// Root Motion
		//if (skeletion.name == "Dummy_root")
		//{
		//	if (pController == _controller)
		//		_root = localTransform;

		//	localTransform.r[3].m128_f32[0] = 0.f;
		//	localTransform.r[3].m128_f32[2] = 0.f;
		//}
	}

	XMMATRIX globalTransform = localTransform * parentTransform;

	/*if (skeletion.parentAnim)
		globalTransform *= *skeletion.parentAnim;*/

	if (-1 != skeletion.id)
	{
		_animationTransforms[skeletion.id] = XMMatrixTranspose(skeletion.offset * globalTransform);
	}

	for (Bone& child : skeletion.children)
	{
		UpdateAnimationTransform(child, globalTransform, pController);
	}
}

XMVECTOR Animator::InterpolationVector3(const std::vector<std::pair<float, Vector3>>& v, const float t)
{
	if (v.empty())
		return XMVectorZero();

	if (v.size() == 1)
		return v[0].second;

	unsigned int index = FindIndex(v, t);
	float time0 = v[index].first;
	float time1 = v[index + 1].first;
	const Vector3& v1 = v[index].second;
	const Vector3& v2 = v[index + 1].second;

	float factor = (t - time0) / (time1 - time0);

	return XMVectorLerp(v1, v2, factor);
}

XMVECTOR Animator::InterpolationVector4(const std::vector<std::pair<float, Vector4>>& v, const float t)
{
	if (v.empty())
		return XMVectorZero();

	if (v.size() == 1)
		return v[0].second;

	unsigned int index = FindIndex(v, t);
	float time0 = v[index].first;
	float time1 = v[index + 1].first;
	const Vector4& v1 = v[index].second;
	const Vector4& v2 = v[index + 1].second;

	float factor = (t - time0) / (time1 - time0);

	return XMQuaternionSlerp(v1, v2, factor);
}

XMMATRIX Animator::BlendAnimation(const Matrix& m0, const Matrix& m1, const float t)
{
	XMVECTOR s0, r0, t0;
	XMVECTOR s1, r1, t1;

	XMMatrixDecompose(&s0, &r0, &t0, XMMatrixTranspose(m0));
	XMMatrixDecompose(&s1, &r1, &t1, XMMatrixTranspose(m1));

	XMVECTOR blendedScale = XMVectorLerp(s0, s1, t);
	XMVECTOR blendedRot = XMQuaternionSlerp(r0, r1, t);
	XMVECTOR blendedPos = XMVectorLerp(t0, t1, t);

	return XMMatrixTranspose(
		   XMMatrixScalingFromVector(blendedScale) * 
		   XMMatrixRotationQuaternion(blendedRot) *
		   XMMatrixTranslationFromVector(blendedPos));
}

void Animator::BoneMasking(const Bone* bone, int mask)
{
	_boneMask[bone->name] = mask;

	for (auto& child : bone->children)
		BoneMasking(&child, mask);
}