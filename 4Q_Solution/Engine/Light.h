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
        void Initialize(const Modules& modules) override;
        void Attach() override;
        void Detach() override;
		void Finalize() override;

    public:
		void SetType(Type type) const;
		void SetIntensity(float intensity) const;
		void SetPosition(float x, float y, float z) const;
		void SetRange(float range) const;
		void SetDirection(float x, float y, float z) const;
		void SetDiffuse(float r, float g, float b, float a) const;
		void SetSpecular(float r, float g, float b, float a) const;
		void SetAmbient(float r, float g, float b, float a) const;
		void SetAttenuation(float constant, float linear, float quadratic) const;
		void SetPositionFromArray(float* pArray) const;
		void SetDirectionFromArray(float* pArray) const;
		void SetDiffuseFromArray(float* pArray) const;
		void SetSpecularFromArray(float* pArray);
		void SetAmbientFromArray(float* pArray);
		void SetMainLight();
		void SetActive(bool active) const;

    private:
        GE::ILight* _geLight;
    };
}
