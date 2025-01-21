#pragma once

namespace Engine::Component
{
    class Light : public GraphicsComponent
    {
	public:
		enum class Type { Directional, Point, Spot };
    public:
        Light();

    public:
        void Initialize() override;
        void Attach() override;
        void Detach() override;
		void Finalize() override;

    public:
		void SetType(Type type);
		void SetIntensity(float intensity);
		void SetPosition(float x, float y, float z);
		void SetRange(float range);
		void SetDirection(float x, float y, float z);
		void SetDiffuse(float r, float g, float b, float a);
		void SetSpecular(float r, float g, float b, float a);
		void SetAmbient(float r, float g, float b, float a);
		void SetAttenuation(float constant, float linear, float quadratic);
		void SetPositionFromArray(float* pArray);
		void SetDirectionFromArray(float* pArray);
		void SetDiffsueFromArray(float* pArray);
		void SetSpecularFromArray(float* pArray);
		void SetAmbientFromArray(float* pArray);

    private:
        GE::ILight* _geLight;
    };
}
