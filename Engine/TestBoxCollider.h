#pragma once

#include "TestCollider.h"
#include "TestGameObject.h"

class TestBoxCollider : public TestCollider
{
	COMPONENT_BODY(TestBoxCollider, TestCollider);
public:
	PROPERTY_FIELD
	{
		REGISTER_OBJECT_REF(TestBoxCollider, owner);
		REGISTER_FIELD(TestBoxCollider, _boxColliderValue);
	}
public:
	i32 _boxColliderValue = 0;
};