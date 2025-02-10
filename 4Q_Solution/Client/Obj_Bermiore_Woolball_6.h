#pragma once
#include "BaseWoolball.h"

class Obj_Bermiore_Woolball_6 : public BaseWoolball
{
public:
	Obj_Bermiore_Woolball_6(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath);

	void Interact() override;


protected:
};