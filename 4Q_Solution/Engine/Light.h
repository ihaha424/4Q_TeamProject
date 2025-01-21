#pragma once

namespace Engine::Component
{
    class Light : public Component
    {
    public:
        Light();

    private:
        GE::ILight* _light;
    };
}
