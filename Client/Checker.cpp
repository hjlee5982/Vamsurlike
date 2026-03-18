#include "pch.h"
#include "Checker.h"
#include "ObjectGenerator.h"
#include "GameObject.h"
#include "Transform.h"
#include "EventManager.h"
#include "Event.h"

void Checker::Awake()
{
	EVENT::Subscribe<GameOverEvent>(&Checker::GameOver, this);
}

void Checker::Update()
{
	Owner()->transform->Translation(-Vector3::Right, _speed * TIMER.DeltaTime());

	auto position = Owner()->transform->GetPosition();

	if (position.x <= -4.f)
	{
		_isColliding = false;
		_generator.lock()->ReturnPool(Owner(), 1);
	}
}

bool Checker::GameOver(const GameOverEvent& e)
{
	_isColliding = false;

	_generator.lock()->ReturnPool(Owner(), 1);

	return false;
}