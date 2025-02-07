#pragma once
#include "StaticObject.h"

class Obj_Buildings_Bermiore_Atelier_2 : public StaticObject
{
public:
	explicit Obj_Buildings_Bermiore_Atelier_2(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath);
	virtual ~Obj_Buildings_Bermiore_Atelier_2() = default;
};

