#include "JSONLoad.h"

json JSONLoad::DeSerialize(const std::string& fileName)
{
    // JSON 파일을 읽어들임
    std::ifstream file(fileName);
    file >> _mapData;

    // 역직렬화
    return _mapData;
}
