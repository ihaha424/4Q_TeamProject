#pragma once

namespace Engine::Physics
{
	struct IObject
	{
		IObject() = default;
		IObject(const IObject& other) = default;
		IObject(IObject&& other) noexcept = default;
		IObject& operator=(const IObject& other) = default;
		IObject& operator=(IObject&& other) noexcept = default;
		virtual ~IObject() = default;

		virtual void		SetName(const char* Name)	= 0;
		virtual const char*	GetName() const				= 0;

		virtual void	SetUserData(ICollision* UserData)	= 0;
		virtual const	ICollision* GetUserData() const		= 0;
		virtual void	ClearUserData()						= 0;

		virtual bool	AttachShape(IShape* shape) = 0;
		virtual bool	DetachShape(IShape* shape) = 0;

		virtual void	SetTranslate(const Utils::Math::Vector3& position) = 0;
		virtual const	Utils::Math::Vector3 GetTranslate() const = 0;
		virtual void	SetRotation(const Utils::Math::Vector4& Rotation) = 0;
		virtual const	Utils::Math::Vector4 GetRotation() const = 0;
		virtual void	SetTransform(const Utils::Math::Transform& transform) = 0;
		virtual const	Utils::Math::Transform GetTransform() const = 0;
	};

	struct Object : IObject
	{
		virtual void Initialize() = 0;
		virtual void Update(float deltaTime) const = 0;
		virtual void Finalize() = 0;
	};
}
