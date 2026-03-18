#pragma once

#include "TestCollider.h"
#include "TestGameObject.h"

#include "Struct.h"

class TestCircleCollider : public TestCollider
{
	COMPONENT_BODY(TestCircleCollider, TestCollider);
public:

	PROPERTY_FIELD
	{
		REGISTER_FIELD(TestCircleCollider, _circleColliderValue);
		REGISTER_FIELD(TestCircleCollider, desc);
		REGISTER_OBJECT_REF(TestCircleCollider, owner);
	}
public:
	i32 _circleColliderValue = 0;
	// TestDesc desc;
};

