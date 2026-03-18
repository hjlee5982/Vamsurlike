#pragma once

#include "TestComponent.h"
#include "TestGameObject.h"

class TestCamera : public TestComponent
{
	COMPONENT_BODY(TestCamera, TestComponent)
private:
	f32 _pov = 0.f;
public:
	static void RegisterFields(TypeInfo* type)
	{
		REGISTER_FIELD(TestCamera, _pov);
		REGISTER_OBJECT_REF(TestCamera, owner);
	}
};

