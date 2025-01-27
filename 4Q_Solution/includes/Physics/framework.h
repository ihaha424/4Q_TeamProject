#pragma once

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.

#ifdef NDEBUG	// _DEBUG / NDEBUG
	#define DEBUG_MODE(Code)
	#define DEBUG_FLAG false
#else
	#define DEBUG_MODE(Code)  Code
	#define DEBUG_FLAG true
#endif


#include <windows.h>

// STL
#include <vector>
#include <map>
#include <functional>

// PhysX Library
#include "PxPhysics.h"
#include "PxPhysicsAPI.h"

// My Physics Utility
#include "Utils.h"

// Explicit Declaration
#define __INTERFACE__ 
#define __CALLBACK__
#define _IN_
#define _OUT_


#define SAFE_DELETE(pointer) \
if(nullptr != pointer) delete pointer\

#define SAFE_RELEASE(pointer) \
if(nullptr != pointer) pointer->release()\


#define OVERRIDE_SET_GET_FUNCTION_CREATOR(NAME, DATA_TYPE) \
void	Set##NAME(const DATA_TYPE& ##NAME)	override; \
const	DATA_TYPE& Get##NAME() const	override\


#define VIRTUAL_SET_GET_FUNCTION_CREATOR(NAME, DATA_TYPE) \
virtual void	Set##NAME(const DATA_TYPE& ##NAME)	= 0; \
virtual const	DATA_TYPE& Get##NAME() const		= 0\
