#pragma once

#include "TestComponent.h"

class TestTransform : public TestComponent
{
	COMPONENT_BODY(TestTransform, TestComponent);
public:
	Vector3 _pos = Vector3::Zero;
	f32 _scale = 0.f;
public:
	static void RegisterFields(TypeInfo* type)
	{
		REGISTER_OBJECT_REF(TestTransform, owner);
		REGISTER_FIELD(TestTransform, _pos);
		REGISTER_FIELD(TestTransform, _scale);
	}
};

