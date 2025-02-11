#pragma once
#include "BaseWoolball.h"

class Obj_Bermiore_Woolball_2 : public BaseWoolball
{
public:
	Obj_Bermiore_Woolball_2(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath);

	void Interact() override;


protected:
};