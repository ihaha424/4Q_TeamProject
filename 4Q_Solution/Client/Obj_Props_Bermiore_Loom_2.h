#pragma once
#include "StaticObject.h"

class Obj_Props_Bermiore_Loom_2 : public StaticObject
{
public:
	explicit Obj_Props_Bermiore_Loom_2(const std::filesystem::path& meshPath, const std::filesystem::path& physicsPath);
	virtual ~Obj_Props_Bermiore_Loom_2() = default;
};

