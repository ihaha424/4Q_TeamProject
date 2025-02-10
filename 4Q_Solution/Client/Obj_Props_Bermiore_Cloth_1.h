#pragma once
#include "StaticObject.h"

class Obj_Props_Bermiore_Cloth_1 : public StaticObject
{
public:
	explicit Obj_Props_Bermiore_Cloth_1(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath);
	virtual ~Obj_Props_Bermiore_Cloth_1() = default;
};

