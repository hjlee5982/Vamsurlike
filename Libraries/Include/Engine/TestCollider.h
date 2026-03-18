#pragma once

#include "TestComponent.h"

class TestCollider : public TestComponent
{
	COMPONENT_BODY(TestCollider, TestComponent)
public:
	PROPERTY_FIELD
	{
		REGISTER_FIELD(TestCollider, colliderSize);
	}
public:
	f32 colliderSize = 0.f;
};

