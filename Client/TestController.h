#pragma once

#include "Component.h"

class TestController : public Component
{
public:
	virtual void Start()  override;
	virtual void Update() override;
public:
	void Move(Vector2 dir);
};

