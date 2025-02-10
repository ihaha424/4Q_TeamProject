#include "pch.h"
#include "CameraRail.h"

Engine::CameraRail::CameraRail() :
	_camera(nullptr),
	_matrix(Math::Matrix::Identity),
	_type(Type::CatmullRom),
	_mode(Mode::Once),
	_state(State::Stopped),
	_direction(Direction::Forward),
	_elapsedTime(0),
	_duration(1.0f)
{
}

void Engine::CameraRail::Prepare(Content::Factory::Component* componentFactory)
{
	_camera = componentFactory->Clone<Component::Camera>(this);
}

void Engine::CameraRail::PreInitialize(const Modules& modules)
{
	Object::PreInitialize(modules);
	_camera->SetParent(&_matrix);
}

void Engine::CameraRail::PostInitialize(const Modules& modules)
{
	Object::PostInitialize(modules);
	AddControlPoint(_transform.position, _transform.rotation, 0);
}

void Engine::CameraRail::PreUpdate(const float deltaTime)
{
	Object::PreUpdate(deltaTime);
	if (_state == State::Playing)
	{
		if (_direction == Direction::Forward) _elapsedTime += deltaTime;
		else _elapsedTime -= deltaTime;
		bool isLast = _elapsedTime >= _duration || _elapsedTime <= 0;
		_elapsedTime = std::clamp(_elapsedTime, 0.0f, _duration);

		float accumulatedDuration = 0.0f;
		size_t toSegmentIndex = 0;
		for (size_t i = 0; i < _controlPoints.size() - 1; ++i)
		{
			accumulatedDuration += _controlPoints[i].duration;
			if (accumulatedDuration >= _elapsedTime)
			{
				toSegmentIndex = i;
				break;
			}
		}
		size_t fromSegmentIndex = toSegmentIndex

		float t = _elapsedTime / _duration;

		switch (_type)
		{
		case Type::Linear:
			Linear(t);
			break;
		case Type::CatmullRom:
			CatmullRom(t);
			break;
		}

		_matrix = Math::Matrix::CreateFromQuaternion(_rotation) * Math::Matrix::CreateTranslation(_position);

		if (isLast)
		{
			switch (_mode)
			{
			case Mode::Once:
				Stop();
				break;
			case Mode::Loop:
				_elapsedTime = 0;
				break;
			case Mode::PingPong:
				_direction = _direction == Direction::Forward ? Direction::Backward : Direction::Forward;
				break;
			}
		}
	}
}

void Engine::CameraRail::AddControlPoint(const Math::Vector3& position, const Math::Vector3& rotation, float duration)
{
	AddControlPoint(position, Math::Quaternion::CreateFromYawPitchRoll(rotation.y, rotation.x, rotation.z), duration);
}

void Engine::CameraRail::AddControlPoint(const Math::Vector3& position, const Math::Quaternion& rotation,
	float duration)
{
	_controlPoints.emplace_back(position, rotation, duration);
	_duration += duration;
}

void Engine::CameraRail::SetDuration(const float duration)
{
	_duration = duration;
}

void Engine::CameraRail::Stop()
{
	_state = State::Stopped;
	_direction = Direction::Forward;
	_elapsedTime = 0;
}

void Engine::CameraRail::DisposeComponents()
{
	_camera->Dispose();
}

void Engine::CameraRail::Linear(float deltaTime)
{
	Math::Vector3::Hermite()
}

void Engine::CameraRail::CatmullRom(float deltaTime)
{
}
