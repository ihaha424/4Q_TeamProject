#include "pch.h"
#include "Vector.h"

DSH::Audio::Vector::Vector() :
	FMOD_VECTOR{ 0.f, 0.f, 0.f }
{
}

DSH::Audio::Vector::Vector(const float x, const float y, const float z):
	FMOD_VECTOR{ x, y, z }
{
}
