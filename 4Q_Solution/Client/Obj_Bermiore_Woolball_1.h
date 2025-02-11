#pragma once
#include "BaseWoolball.h"

class Obj_Bermiore_Woolball_1 : public BaseWoolball
{
public:
	Obj_Bermiore_Woolball_1(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath);

	void Interact() override;


protected:
};

