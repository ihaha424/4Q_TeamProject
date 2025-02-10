#pragma once

namespace Engine
{
	class CameraRail : public Object
	{
	public:
		enum class Type
		{
			Linear,
			Bezier,
			CatmullRom,
			CubicSpline,
			Lagrange
		};

		enum class Mode
		{
			Once,
			Loop,
			PingPong
		};

		enum class State
		{
			Playing,
			Paused,
			Stopped
		};

		enum class Direction
		{
			Forward,
			Backward
		};

	private:
		struct ControlPoint;
	public:
		CameraRail();

		void Prepare(Content::Factory::Component* componentFactory) override;
		void PreInitialize(const Modules& modules) override;
		void PreUpdate(float deltaTime) override;

		void AddControlPoint(Math::Vector3 position, Math::Vector3 rotation, float duration);
		void AddControlPoint(Math::Vector3 position, Math::Quaternion rotation, float duration);

	protected:
		void DisposeComponents() override;

	private:
		Component::Camera* _camera;
		Math::Matrix _matrix;

		Type _type;
		Mode _mode;
		State _state;
		Direction _direction;

		std::vector<ControlPoint> _controlPoints;

		struct ControlPoint
		{
			ControlPoint(const Math::Vector3 position, const Math::Quaternion rotation, const float duration):
				 duration(duration)
			{
				matrix = Math::Matrix::CreateFromQuaternion(rotation);
				matrix.Translation(position);
			}
			Math::Matrix matrix;
			float duration;
		};
	};
}
