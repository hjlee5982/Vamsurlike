#include "pch.h"
#include "TestController.h"
#include "InputSystem.h"

void TestController::Start()
{
	INPUT.FindAction("Move")->performedValue = [this](Vector2 v) { Move(v); };
}

void TestController::Update()
{
}

void TestController::Move(Vector2 dir)
{
	//std::cout << "X : " << dir.x << ", Y : "<< dir.y << std::endl;

	Vector3 dir3 = Vector3(dir.x, dir.y, 0);

	Owner()->transform->_localPosition += dir3 * TIMER.DeltaTime() * 5;
}