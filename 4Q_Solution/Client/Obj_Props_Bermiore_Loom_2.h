#pragma once
#include "StaticObject.h"

class Obj_Props_Bermiore_Loom_2 : public StaticObject
{
public:
	explicit Obj_Props_Bermiore_Loom_2(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath);
	virtual ~Obj_Props_Bermiore_Loom_2() = default;
};

