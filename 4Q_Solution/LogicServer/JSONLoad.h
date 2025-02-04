#pragma once
#include <nlohmann/json.hpp>
#include <fstream>

class JSONLoad
{
	using json = nlohmann::json;
public:
	void deserializeJson(const std::string& fileName);


private:
	json _mapData;
	
};

