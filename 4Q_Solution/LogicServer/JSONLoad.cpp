#include "JSONLoad.h"

void JSONLoad::deserializeJson(const std::string& fileName)
{
    // JSON 파일을 읽어들임
    std::ifstream file(fileName);
    json j;
    file >> j;

    // 역직렬화
    for (const auto& item : j["items"]) {
        ChildData data;
        data.name = item["name"];
        data.position = { item["position"]["x"], item["position"]["y"], item["position"]["z"] };
        data.rotation = { item["rotation"]["x"], item["rotation"]["y"], item["rotation"]["z"], item["rotation"]["w"] };
        data.scale = { item["scale"]["x"], item["scale"]["y"], item["scale"]["z"] };

        // 출력
        std::cout << "Name: " << data.name << std::endl;
        std::cout << "Position: (" << data.position.x << ", " << data.position.y << ", " << data.position.z << ")" << std::endl;
        std::cout << "Rotation: (" << data.rotation.x << ", " << data.rotation.y << ", " << data.rotation.z << ", " << data.rotation.w << ")" << std::endl;
        std::cout << "Scale: (" << data.scale.x << ", " << data.scale.y << ", " << data.scale.z << ")" << std::endl;
        std::cout << "--------------" << std::endl;
    }
}
