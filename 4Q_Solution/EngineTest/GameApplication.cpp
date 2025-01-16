#include "pch.h"
#include "GameApplication.h"

#include "TestWorld.h"

GameApplication::GameApplication(const HINSTANCE instanceHandle):
	Application(instanceHandle, L"Test", SIZE{ 1920, 1080 })
{
}
