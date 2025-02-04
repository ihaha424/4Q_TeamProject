#pragma once
#include "json.hpp"
#include <fstream>

using json = nlohmann::json;

class JSONLoad
{
	
public:
	json DeSerialize(const std::string& fileName);


private:
	json _mapData;
	
};

