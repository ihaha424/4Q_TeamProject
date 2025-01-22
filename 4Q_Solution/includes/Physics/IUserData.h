#pragma once

namespace PhysicsEngineAPI
{
	class ICollision;
	__INTERFACE__
	class IUserData
	{
	public:


		virtual void SetName(const char* Name)	= 0; 
		virtual const char* GetName() const		= 0;

		virtual void SetUserData(ICollision* UserData)	= 0; 
		virtual const ICollision* GetUserData() const	= 0;


		virtual void	ClearUserData()	= 0;
		//virtual bool	IsUserData()	= 0;
	};
}

