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
	_totalDuration(1.0f)
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
		const bool isLast = _elapsedTime >= _totalDuration || _elapsedTime <= 0;
		_elapsedTime = std::clamp(_elapsedTime, 0.0f, _totalDuration);

		size_t p1Index = 0;
		size_t p2Index = 0;

		float accumulatedDuration = 0.0f;

		for (size_t i = 1; i < _controlPoints.size() - 1; i++)
		{
			if (accumulatedDuration += _controlPoints[i].duration >= _elapsedTime)
			{
				p2Index = i;
				p1Index = i - 1;
				break;
			}
			accumulatedDuration += _controlPoints[i].duration;
		}

		const ControlPoint& p0 = _controlPoints[p1Index == 0 ? 0 : p1Index -1];
		const ControlPoint& p1 = _controlPoints[p1Index];
		const ControlPoint& p2 = _controlPoints[p2Index];
		const ControlPoint& p3 = _controlPoints[p2Index == _controlPoints.size() - 1 ? p2Index : p2Index + 1];

		const float t = (_elapsedTime - accumulatedDuration) / p2.duration;

		switch (_type)
		{
		case Type::Linear:
			_position = Linear(p1.position, p2.position, t);
			break;
		case Type::CatmullRom:
			_position = CatmullRom(p0.position, p1.position, p2.position, p3.position, t);
			break;
		}

		_rotation = Math::Quaternion::Slerp(p1.rotation, p2.rotation, t);

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

void Engine::CameraRail::AddControlPoint(const Math::Vector3& position, const Math::Vector3& rotation, const float duration)
{
	AddControlPoint(position, Math::Quaternion::CreateFromYawPitchRoll(rotation.y, rotation.x, rotation.z), duration);
}

void Engine::CameraRail::AddControlPoint(const Math::Vector3& position, const Math::Quaternion& rotation,
	float duration)
{
	_controlPoints.emplace_back(position, rotation, duration);
	_totalDuration += duration;
}

void Engine::CameraRail::SetDuration(const float duration)
{
	_totalDuration = duration;
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

Engine::Math::Vector3 Engine::CameraRail::Linear(const Math::Vector3& p0, const Math::Vector3& p1, float deltaTime)
{
	return Math::Vector3::Lerp(p0, p1, deltaTime);
}

Engine::Math::Vector3 Engine::CameraRail::CatmullRom(const Math::Vector3& p0, const Math::Vector3& p1, const Math::Vector3& p2,
	const Math::Vector3& p3, const float deltaTime)
{
	return Math::Vector3::CatmullRom(p0, p1, p2, p3, deltaTime);
}
