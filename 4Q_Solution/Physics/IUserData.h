#pragma once

namespace PhysicsEngineAPI
{
	__INTERFACE__
	EXTERN_C class PHYSICS_API IUserData
	{
	public:
		virtual ~IUserData() = default;


		virtual void SetName(const char* Name)	= 0; 
		virtual const char* GetName() const		= 0;

		virtual void SetUserData(ICollision* UserData)	= 0; 
		virtual const ICollision* GetUserData() const	= 0;


		virtual void	ClearUserData()	= 0;
		//virtual bool	IsUserData()	= 0;
	};
}

