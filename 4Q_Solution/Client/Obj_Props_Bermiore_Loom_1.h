#pragma once
#include "StaticObject.h"

class Obj_Props_Bermiore_Loom_1 : public StaticObject
{
public:
	explicit Obj_Props_Bermiore_Loom_1(const std::filesystem::path& meshPath, const std::filesystem::path& physicsPath);
	virtual ~Obj_Props_Bermiore_Loom_1() = default;
};

