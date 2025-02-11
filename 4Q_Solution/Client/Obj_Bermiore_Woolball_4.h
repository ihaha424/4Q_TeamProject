#pragma once
#include "BaseWoolball.h"

class Obj_Bermiore_Woolball_4 : public BaseWoolball
{
public:
	Obj_Bermiore_Woolball_4(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath);

	void Interact() override;


protected:
};