#include "pch.h"
#include "EmptyWorld.h"

#include "GlobalLight.h"
#include "SimpleCamera.h"
#include "SkyBox.h"

void EmptyWorld::Prepare(Engine::Content::Factory::Object* objectFactory)
{
	objectFactory->Clone<GlobalLight>(this);
	objectFactory->Clone<SkyBox>(this);
	objectFactory->Clone<SimpleCamera>(this);
}
