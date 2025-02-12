#pragma once

namespace Engine
{
	class CameraRail : public Object
	{
	public:
		enum class Type : unsigned char;

		enum class Mode : unsigned char;

		enum class State : unsigned char;

		enum class Direction : unsigned char;

	private:
		struct ControlPoint;
	public:
		CameraRail();

		void Prepare(Content::Factory::Component* componentFactory) override;
		void PreInitialize(const Modules& modules) override;
		void PostInitialize(const Modules& modules) override;
		void PreUpdate(float deltaTime) override;

		void AddControlPoint(const Math::Vector3& position, const Math::Vector3& rotation, float duration);
		void AddControlPoint(const Math::Vector3& position, const Math::Quaternion& rotation, float duration);

		void SetDuration(float duration);

		void Play();
		void Pause();
		void Stop();

	protected:
		void DisposeComponents() override;

	private:
		static Math::Vector3 Linear(const Math::Vector3& p0, const Math::Vector3& p1, float deltaTime);
		static Math::Vector3 CatmullRom(const Math::Vector3& p0, const Math::Vector3& p1, const Math::Vector3& p2, const Math::Vector3& p3, float deltaTime);

		Component::Camera* _camera;

		Math::Vector3 _position;
		Math::Quaternion _rotation;
		Math::Matrix _matrix;

		Type _type;
		Mode _mode;
		State _state;
		Direction _direction;

		float _elapsedTime;
		float _totalDuration;

		std::vector<ControlPoint> _controlPoints;

	public:
		enum class Type : unsigned char
		{
			Linear,
			CatmullRom
		};

		enum class Mode : unsigned char
		{
			Once,
			Loop,
			PingPong
		};

		enum class State : unsigned char
		{
			Playing,
			Paused,
			Stopped
		};

		enum class Direction : unsigned char
		{
			Forward,
			Backward
		};

	private:
		struct ControlPoint
		{
			ControlPoint(const Math::Vector3 position, const Math::Quaternion rotation, const float duration):
				position(position), rotation(rotation), duration(duration)
			{
			}
			Math::Vector3 position;
			Math::Quaternion rotation;
			float duration;
		};
	};

	inline void CameraRail::Pause()
	{
		_state = State::Paused;
	}

	inline void CameraRail::Play()
	{
		_state = State::Playing;
	}
}
