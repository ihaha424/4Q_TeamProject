#pragma once
class Trigger_SudiumBGM : public Engine::Object
{
public:
	explicit Trigger_SudiumBGM() = default;

	void SetIsPublic(bool isPublic);
	void SetisDynamic(bool isDynamic);
	void SetHasMesh(bool hasMesh);
	void SetBoxScale(Engine::Math::Vector3 boxScale);
	void SetBoxPosition(Engine::Math::Vector3 boxPosition);
	void SetIsSphere(bool isSphere);

	// Object을(를) 통해 상속됨
	void Prepare(Engine::Content::Factory::Component* componentFactory) override;

	void DisposeComponents() override;
	void PreInitialize(const Engine::Modules& modules) override;

protected:
	TriggerBox* _trigger;
	Engine::Component::BackgroundMusic* _sound;

	bool _isPublic;
	bool _isDynamic;
	bool _hasMesh;
	bool _isSphere;
	Engine::Math::Vector3 _boxScale;
	Engine::Math::Vector3 _boxPosition;
};

