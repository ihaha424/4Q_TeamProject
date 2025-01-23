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

		void		SetName(const char* Name);
		const char*	GetName() const;

		void	SetUserData(ICollision* UserData);
		const	ICollision* GetUserData() const;
		void	ClearUserData();

		bool	AttachShape(IShape* shape);
		bool	DetachShape(IShape* shape);

		void	SetTranslate(const Math::Vector3& position);
		const	Math::Vector3 GetTranslate() const;
		void	SetRotation(const Math::Vector4& Rotation);
		const	Math::Vector4 GetRotation() const;
		void	SetTransform(const Math::Transform& transform);
		const	Math::Transform GetTransform() const;
	};

	struct Object : IObject
	{
		virtual void Initialize() = 0;
		virtual void Update(float deltaTime) const = 0;
		virtual void Finalize() = 0;
	};
}
