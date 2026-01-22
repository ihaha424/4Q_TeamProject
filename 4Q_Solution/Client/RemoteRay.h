#pragma once
//#include "RayState.h"

class RemoteRay : public Remote
{
public:
	RemoteRay(std::filesystem::path&& meshPath);
};