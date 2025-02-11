#pragma once
#include "BaseWoolball.h"

class Obj_Bermiore_Woolball_5 : public BaseWoolball
{
public:
	Obj_Bermiore_Woolball_5(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath);

	void Interact() override;


protected:
};